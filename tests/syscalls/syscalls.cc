/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl tests for simple syscalls
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "native_client/src/include/nacl_assert.h"
#include "native_client/src/trusted/service_runtime/include/sys/nacl_syscalls.h"

#define PRINT_HEADER 0
#define TEXT_LINE_SIZE 1024

/*
 * TODO(sbc): remove this test once these declarations get added to the prebuilt
 * newlib toolchain
 */
#ifndef __GLIBC__
extern "C" int gethostname(char *name, size_t len);
extern "C" int utimes(const char *filename, const struct timeval times[2]);
#endif

/*
 * function failed(testname, msg)
 *   print failure message and exit with a return code of -1
 */
bool failed(const char *testname, const char *msg) {
  printf("TEST FAILED: %s: %s\n", testname, msg);
  return false;
}

/*
 * function passed(testname, msg)
 *   print success message
 */
bool passed(const char *testname, const char *msg) {
  printf("TEST PASSED: %s: %s\n", testname, msg);
  return true;
}

/*
 * Split filename into basename and dirname.
 * The argument is modified in place such that it
 * becomes the dirname and the basename is returned.
 */
static char *split_name(char *full_name) {
  // Strip off the trailing filename
  char *basename = strrchr(full_name, '/');
  if (basename == NULL) {
    basename = strrchr(full_name, '\\');
    ASSERT_NE_MSG(basename, NULL, "test_file contains no dir seperator");
    if (!basename)
      return NULL;
  }
  basename[0] = '\0';
  return basename + 1;
}

// In case a previous run of this test failed and left the file behind,
// remove the file first.
// TODO(mseaborn): It would be cleaner to create a guaranteed-empty temp
// directory instead of doing this.
static void ensure_file_is_absent(const char *filename) {
  int result = unlink(filename);
  if (result != 0) {
    ASSERT_EQ(errno, ENOENT);
  }
}

/*
 * function test*()
 *
 *   Simple tests follow below.  Each test may call one or more
 *   of the functions above.  They all have a boolean return value
 *   to indicate success (all tests passed) or failure (one or more
 *   tests failed)  Order matters - the parent should call
 *   test1() before test2(), and so on.
 */

bool test_sched_yield() {
  if (sched_yield()) {
    printf("sched_yield failed\n");
    return false;
  }
  return true;
}

bool test_sysconf() {
  // TODO(hamaji): Implement _SC_NPROCESSORS_ONLN for newlib based
  // non-SFI mode. Note that this test works for unsandboxed mode.
  if (NONSFI_MODE)
    return true;
  int rv;
  rv = sysconf(_SC_NPROCESSORS_ONLN);
  if (rv == -1) {
    printf("failed to get nprocs\n");
    return false;
  }
  if (rv < 1) {
    printf("got strange number of processors: %d\n", rv);
    return false;
  }
  // test sysconf on an invalid input.
  rv = sysconf(-1);
  if (rv != -1) {
    printf("succeeded on unsupported\n");
    return false;
  }
  return true;
}

// Simple test that chdir returns zero for '.'.  chdir gets more
// significant testing as part of the getcwd test.
bool test_chdir() {
  int rtn = chdir(".");
  ASSERT_EQ_MSG(rtn, 0, "chdir() failed");

  return passed("test_chdir", "all");
}

bool test_mkdir_rmdir(const char *test_file) {
  // Use a temporary direcotry name alongside the test_file which
  // was passed in.
  char dirname[PATH_MAX];
  strncpy(dirname, test_file, PATH_MAX);
  split_name(dirname);

  ASSERT(strlen(dirname) + 6 < PATH_MAX);
  strncat(dirname, "tmpdir", 6);

  // Attempt to remove the directory in case it already exists
  // from a previous test run.
  if (rmdir(dirname) != 0)
    ASSERT_EQ_MSG(errno, ENOENT, "rmdir() failed to cleanup existing dir");

  char cwd[PATH_MAX];
  char *cwd_rtn = getcwd(cwd, PATH_MAX);
  ASSERT_EQ_MSG(cwd_rtn, cwd, "getcwd() failed");

  int rtn = mkdir(dirname, S_IRUSR | S_IWUSR | S_IXUSR);
  ASSERT_EQ_MSG(rtn, 0, "mkdir() failed");

  rtn = rmdir(dirname);
  ASSERT_EQ_MSG(rtn, 0, "rmdir() failed");

  rtn = rmdir("This file does not exist");
  ASSERT_EQ_MSG(rtn, -1, "rmdir() failed to fail");
  ASSERT_EQ_MSG(errno, ENOENT, "rmdir() failed to generate ENOENT");

  return passed("test_mkdir_rmdir", "all");
}

bool test_getcwd() {
  char dirname[PATH_MAX] = { '\0' };
  char newdir[PATH_MAX] = { '\0' };
  char parent[PATH_MAX] = { '\0' };

  char *rtn = getcwd(dirname, PATH_MAX);
  ASSERT_EQ_MSG(rtn, dirname, "getcwd() failed to return dirname");
  ASSERT_NE_MSG(strlen(dirname), 0, "getcwd() failed to set valid dirname");

  // Calculate parent folder.
  strncpy(parent, dirname, PATH_MAX);
  char *basename_start = strrchr(parent, '/');
  if (basename_start == NULL) {
    basename_start = strrchr(parent, '\\');
    ASSERT_NE_MSG(basename_start, NULL, "test_file contains no dir seperator");
  }
  basename_start[0] = '\0';

  int retcode = chdir("..");
  ASSERT_EQ_MSG(retcode, 0, "chdir() failed");

  rtn = getcwd(newdir, PATH_MAX);
  ASSERT_EQ_MSG(rtn, newdir, "getcwd() failed");

  ASSERT_MSG(strcmp(newdir, parent) == 0, "getcwd() failed after chdir");
  retcode = chdir(dirname);
  ASSERT_EQ_MSG(retcode, 0, "chdir() failed");

  rtn = getcwd(dirname, 2);
  ASSERT_EQ_MSG(rtn, NULL, "getcwd() failed to fail");
  ASSERT_EQ_MSG(errno, ERANGE, "getcwd() failed to generate ERANGE");

  return passed("test_getcwd", "all");
}

bool test_unlink(const char *test_file) {
  int rtn;
  struct stat buf;
  char temp_file[PATH_MAX];
  snprintf(temp_file, PATH_MAX, "%s.tmp_unlink", test_file);
  temp_file[PATH_MAX - 1] = '\0';

  int fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  ASSERT_MSG(fd >= 0, "open() failed");

  rtn = close(fd);
  ASSERT_EQ_MSG(rtn, 0, "close() failed");

  rtn = stat(temp_file, &buf);
  ASSERT_EQ_MSG(rtn, 0, "stat() failed");

  rtn = unlink(temp_file);
  ASSERT_EQ_MSG(rtn, 0, "unlink() failed");

  rtn = stat(temp_file, &buf);
  ASSERT_NE_MSG(rtn, 0, "unlink() failed to remove file");

  rtn = unlink(temp_file);
  ASSERT_NE_MSG(rtn, 0, "unlink() failed to fail");

  return passed("test_unlink", "all");
}

bool test_rename(const char *test_file) {
  int rtn;
  struct stat buf;
  char filename1[PATH_MAX];
  char filename2[PATH_MAX];
  snprintf(filename1, PATH_MAX, "%s.tmp1", test_file);
  snprintf(filename2, PATH_MAX, "%s.tmp2", test_file);

  // Create a test file and verify that we can stat() it.
  int fd = open(filename1, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  ASSERT_MSG(fd >= 0, "open() failed");
  rtn = close(fd);
  ASSERT_EQ_MSG(rtn, 0, "close() failed");

  rtn = stat(filename1, &buf);
  ASSERT_EQ_MSG(rtn, 0, "stat() failed");

  // Rename the test file and verify that the old file is no
  // longer stat()-able.
  rtn = rename(filename1, filename2);
  ASSERT_EQ_MSG(rtn, 0, "rename() failed");

  rtn = stat(filename2, &buf);
  ASSERT_EQ_MSG(rtn, 0, "stat() of new file failed");

  rtn = stat(filename1, &buf);
  ASSERT_NE_MSG(rtn, 0, "stat() of old name should fail after rename");

  ASSERT_EQ(remove(filename2), 0);
  return passed("test_rename", "all");
}

bool test_link(const char *test_file) {
  struct stat buf;
  struct stat buf_orig;
  char link_filename[PATH_MAX];
  char target_filename[PATH_MAX];
  snprintf(target_filename, PATH_MAX, "%s.target", test_file);
  snprintf(link_filename, PATH_MAX, "%s.link", test_file);

  ensure_file_is_absent(target_filename);
  ensure_file_is_absent(link_filename);

  // Create link target with some dummy data
  int fd = open(target_filename, O_WRONLY | O_CREAT, S_IRWXU);
  ASSERT(fd >= 0);
  ASSERT_EQ(write(fd, "123", 3), 3);
  ASSERT_EQ(close(fd), 0);

  int rtn = link(target_filename, link_filename);
  if (rtn != 0 && errno == ENOSYS) {
    // If we get ENOSYS, assume we are on Windows, where link() is expected
    // to fail.
    return passed("test_link", "all");
  }
  ASSERT_EQ(rtn, 0);

  // Verify that the new file is a regular file and that changes to it are
  // mirrored in the original file.
  ASSERT_EQ(stat(link_filename, &buf), 0);
  ASSERT_EQ(stat(target_filename, &buf_orig), 0);
  ASSERT(S_ISREG(buf.st_mode));
  ASSERT(S_ISREG(buf_orig.st_mode));

  ASSERT_EQ(buf_orig.st_size, 3);
  ASSERT_EQ(buf_orig.st_size, buf.st_size);

  // Write some bytes to the new file
  fd = open(link_filename, O_WRONLY);
  ASSERT(fd >= 0);
  ASSERT_EQ(write(fd, "test", 4), 4);
  ASSERT_EQ(close(fd), 0);

  // Verify that the two files are still the same size
  ASSERT_EQ(stat(link_filename, &buf), 0);
  ASSERT_EQ(stat(target_filename, &buf_orig), 0);
  ASSERT(S_ISREG(buf.st_mode));
  ASSERT(S_ISREG(buf_orig.st_mode));
  ASSERT_EQ(buf_orig.st_size, buf.st_size);
  ASSERT_EQ(buf_orig.st_size, 4);

  ASSERT_EQ(remove(link_filename), 0);
  ASSERT_EQ(remove(target_filename), 0);
  return passed("test_link", "all");
}

// This tests symlink/readlink and lstat.
bool test_symlinks(const char *test_file) {
  char dirname[PATH_MAX];
  char link_filename[PATH_MAX];
  struct stat buf;

  // Test that lstat of the test_file works
  ASSERT_EQ(lstat(test_file, &buf), 0);
  ASSERT_EQ(S_ISREG(buf.st_mode), 1);

  // Split filename into basename and dirname.
  strncpy(dirname, test_file, PATH_MAX);
  char *basename = split_name(dirname);

  snprintf(link_filename, PATH_MAX, "%s.link", test_file);

  ensure_file_is_absent(link_filename);

  // Create this link
  int rtn = symlink(basename, link_filename);
  if (rtn != 0 && errno == ENOSYS) {
    // If we get ENOSYS, assume we are on Windows, where symlink() and
    // readlink() are expected to fail.
    return passed("test_symlinks", "all");
  }
  ASSERT_EQ(rtn, 0);

  // Check the lstat() and stat of the link
  ASSERT_EQ(lstat(link_filename, &buf), 0);
  ASSERT_NE_MSG(S_ISLNK(buf.st_mode), 0, "lstat of link failed to be ISLNK");
  ASSERT_EQ_MSG(S_ISREG(buf.st_mode), 0, "lstat of link should not be ISREG");

  ASSERT_EQ(stat(link_filename, &buf), 0);
  ASSERT_EQ_MSG(S_ISLNK(buf.st_mode), 0, "stat of symlink should not ISLNK");
  ASSERT_NE_MSG(S_ISREG(buf.st_mode), 0, "stat of symlink should report ISREG");

  // Test readlink().
  char link_dest[PATH_MAX];
  memset(link_dest, 0x77, sizeof(link_dest));
  ssize_t result = readlink(link_filename, link_dest, sizeof(link_dest));
  ASSERT_EQ(result, (ssize_t) strlen(basename));
  ASSERT_EQ(memcmp(link_dest, basename, result), 0);
  // readlink() should not write a null terminator.
  ASSERT_EQ(link_dest[result], 0x77);

  // Test readlink() with a truncated result.
  memset(link_dest, 0x77, sizeof(link_dest));
  result = readlink(link_filename, link_dest, 1);
  ASSERT_EQ(result, 1);
  ASSERT_EQ(link_dest[0], basename[0]);
  // The rest of the buffer should not be modified.
  for (size_t i = 1; i < sizeof(link_dest); ++i)
    ASSERT_EQ(link_dest[i], 0x77);

  // calling symlink again should yield EEXIST.
  ASSERT_EQ(symlink(test_file, link_filename), -1);
  ASSERT_EQ(errno, EEXIST);
  ASSERT_EQ(remove(link_filename), 0);

  return passed("test_symlinks", "all");
}

bool test_chmod(const char *test_file) {
  struct stat buf;
  char temp_file[PATH_MAX];
  snprintf(temp_file, PATH_MAX, "%s.tmp_chmod", test_file);

  int fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  ASSERT(fd >= 0);
  ASSERT_EQ(close(fd), 0);

  ASSERT_EQ(stat(temp_file, &buf), 0);
  ASSERT_EQ(buf.st_mode & ~S_IFMT, S_IRUSR | S_IWUSR);

  // change the file to readonly and verify the change
  ASSERT_EQ(chmod(temp_file, S_IRUSR), 0);
  ASSERT_EQ(stat(temp_file, &buf), 0);
  ASSERT_EQ(buf.st_mode & ~S_IFMT, S_IRUSR);
  ASSERT(open(temp_file, O_WRONLY) < 0);

  ASSERT_EQ(remove(temp_file), 0);
  return passed("test_chmod", "all");
}

bool test_access(const char *test_file) {
  char temp_access[PATH_MAX];
  snprintf(temp_access, PATH_MAX, "%s.tmp_access", test_file);

  ASSERT_EQ(access(test_file, F_OK), 0);
  ASSERT_EQ(access(test_file, R_OK), 0);
  ASSERT_EQ(access(test_file, W_OK), 0);

  ASSERT_EQ(access(temp_access, F_OK), -1);
  ASSERT_EQ(access(temp_access, R_OK), -1);
  ASSERT_EQ(access(temp_access, W_OK), -1);

  /*
   * We can't test the X bit here since it's not consistent across platforms.
   * On win32 there is no equivalent so we always return true.  On Mac/Linux
   * the underlying X bit is reported.
   */
  // ASSERT_EQ(access(test_file, X_OK), -1);
  // ASSERT_EQ(access(temp_access, X_OK), -1);

  // Create a read-only file
  int fd = open(temp_access, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
  ASSERT(fd > 0);
  ASSERT_EQ(close(fd), 0);

  ASSERT_EQ(access(temp_access, F_OK), 0);
  ASSERT_EQ(access(temp_access, R_OK), 0);
  ASSERT_EQ(access(temp_access, W_OK), -1);
  ASSERT_EQ(remove(temp_access), 0);

  return passed("test_access", "all");
}

bool test_utimes(const char *test_file) {
  // TODO(mseaborn): Implement utimes for unsandboxed mode.
  if (NONSFI_MODE)
    return true;
  struct timeval times[2];
  // utimes() is currently not implemented and should always
  // fail with ENOSYS
  ASSERT_EQ(utimes("dummy", times), -1);
  ASSERT_EQ(errno, ENOSYS);
  return passed("test_utimes", "all");
}

bool test_truncate(const char *test_file) {
  char temp_file[PATH_MAX];
  snprintf(temp_file, PATH_MAX, "%s.tmp_truncate", test_file);

  char buffer[100];
  char read_buffer[200];
  struct stat buf;
  for (size_t i = 0; i < sizeof(buffer); i++)
    buffer[i] = i;

  // Write 100 sequential chars to the test file.
  int fd = open(temp_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
  ASSERT(fd >= 0);
  ASSERT_EQ(100, write(fd, buffer, 100));
  ASSERT_EQ(0, close(fd));

  ASSERT_EQ(stat(temp_file, &buf), 0);
  ASSERT_EQ(buf.st_size, 100);

  // truncate the file beyond its current length
  ASSERT_EQ(truncate(temp_file, 200), 0);
  ASSERT_EQ(stat(temp_file, &buf), 0);
  ASSERT_EQ(buf.st_size, 200);

  // Verify the new content, which should not be 100
  // bytes of sequential chars and 100 bytes of '\0'
  fd = open(temp_file, O_RDONLY);
  ASSERT(fd >= 0);
  ASSERT_EQ(read(fd, read_buffer, 200), 200);
  ASSERT_EQ(memcmp(read_buffer, buffer, 100), 0);
  for (int i = 100; i < 200; i++)
    ASSERT_EQ(read_buffer[i], 0);
  ASSERT_EQ(0, close(fd));

  // Now truncate the file to a size smaller than the
  // original
  ASSERT_EQ(truncate(temp_file, 50), 0);
  ASSERT_EQ(stat(temp_file, &buf), 0);
  ASSERT_EQ(buf.st_size, 50);

  fd = open(temp_file, O_RDONLY);
  ASSERT(fd >= 0);
  ASSERT_EQ(read(fd, read_buffer, 50), 50);
  ASSERT_EQ(memcmp(read_buffer, buffer, 50), 0);
  ASSERT_EQ(0, close(fd));

  ASSERT_EQ(remove(temp_file), 0);
  return passed("test_truncate", "all");
}

// open() returns the new file descriptor, or -1 if an error occurred
bool test_open(const char *test_file) {
  int fd;
  const char *testname = "test_open";

  // file OK, flag OK
  fd = open(test_file, O_RDONLY);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDONLY)");
  close(fd);

  errno = 0;
  // file does not exist, flags OK
  fd = open("testdata/file_none.txt", O_RDONLY);
  if (fd != -1)
    return failed(testname, "open(testdata/file_none.txt, O_RDONLY)");
  // no such file or directory
  if (ENOENT != errno)
    return failed(testname, "ENOENT != errno");
  close(fd);

  // file OK, flags OK, mode OK
  fd = open(test_file, O_WRONLY, S_IRUSR);
  if (fd == -1)
    return failed(testname, "open(test_file, O_WRONLY, S_IRUSR)");
  close(fd);

  // too many args
  fd = open(test_file, O_RDWR, S_IRUSR, O_APPEND);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDWR, S_IRUSR, O_APPEND)");
  close(fd);

  // directory OK
  fd = open(".", O_RDONLY);
  if (fd == -1)
    return failed(testname, "open(., O_RDONLY)");
  close(fd);

  errno = 0;
  // directory does not exist
  fd = open("nosuchdir", O_RDONLY);
  if (fd != -1)
    return failed(testname, "open(nosuchdir, O_RDONLY)");
  // no such file or directory
  if (ENOENT != errno)
    return failed(testname, "ENOENT != errno");
  close(fd);

  return passed(testname, "all");
}

bool test_stat(const char *test_file) {
  struct stat buf;

  // Test incoming test_file for read and write permission.
  ASSERT_EQ(stat(test_file, &buf), 0);
  ASSERT_MSG(buf.st_mode & S_IRUSR, "stat() failed to report S_IRUSR");
  ASSERT_MSG(buf.st_mode & S_IWUSR, "stat() failed to report S_IWUSR");

  // Test a new read-only file
  // The current unlink() implemenation in the sel_ldr for Windows
  // doesn't support removing read-only files.
  // TODO(sbc): enable this part of the test once this gets fixed.
#if 0
  char buffer[PATH_MAX];
  snprintf(buffer, PATH_MAX, "%s.readonly", test_file);
  buffer[PATH_MAX - 1] = '\0';
  unlink(buffer);
  ASSERT_EQ(stat(buffer, &buf), -1);
  int fd = open(buffer, O_RDWR | O_CREAT, S_IRUSR);
  ASSERT_NE(fd, -1);
  ASSERT_EQ(close(fd), 0);
  ASSERT_EQ(stat(buffer, &buf), 0);
  ASSERT_MSG(buf.st_mode & S_IRUSR, "stat() failed to report S_IRUSR");
  ASSERT_MSG(!(buf.st_mode & S_IWUSR), "S_IWUSR report for a read-only file");
#endif

  // Windows doesn't support the concept of write only files,
  // so we can't test this case.

  return passed("test_stat", "all");
}

// close() returns 0 on success, -1 on error
bool test_close(const char *test_file) {
  int fd;
  int ret_val;
  const char *testname = "test_close";

  // file OK
  fd = open(test_file, O_RDWR);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDWR)");
  ret_val = close(fd);
  if (ret_val == -1)
    return failed(testname, "close(test_file, O_RDWR)");

  // file OK
  fd = open(test_file, O_RDWR);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDWR)");
  // close on wrong fd not OK
  errno = 0;
  ret_val = close(fd+1);
  if (ret_val != -1)
    return failed(testname, "close(fd+1)");
  // bad file number
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");
  ret_val = close(fd);
  if (ret_val == -1)
    return failed(testname, "close(test_file, O_RDWR)");

  // file not OK
  fd = open("file_none.txt", O_WRONLY);
  if (fd != -1)
    return failed(testname, "open(file_none.txt, O_WRONLY)");
  errno = 0;
  ret_val = close(fd);
  if (ret_val == 0)
    return failed(testname, "close(file_none.txt, O_WRONLY)");
  // bad file number
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");

  // directory OK
  // Linux's open() (unsandboxed) does not allow O_RDWR on a directory.
  // TODO(mseaborn): sel_ldr should reject O_RDWR on a directory too.
  if (!NONSFI_MODE) {
    fd = open(".", O_RDWR);
    if (fd == -1)
      return failed(testname, "open(., O_RDWR)");
    ret_val = close(fd);
    if (ret_val == -1)
      return failed(testname, "close(., O_RDWR)");
  }

  // directory not OK
  fd = open("nosuchdir", O_RDWR);
  if (fd != -1)
    return failed(testname, "open(nosuchdir, O_RDWR)");
  errno = 0;
  ret_val = close(fd);
  if (ret_val == 0)
    return failed(testname, "close(nosuchdir, O_RDWR)");
  // bad file number
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");

  return passed(testname, "all");
}

// read() returns the number of bytes read on success (0 indicates end
// of file), -1 on error
bool test_read(const char *test_file) {
  int fd;
  int ret_val;
  char out_char[5];
  const char *testname = "test_read";

  fd = open(test_file, O_RDONLY);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDONLY)");

  // fd OK, buffer OK, count OK
  ret_val = read(fd, out_char, 1);
  if (ret_val == -1)
    return failed(testname, "read(fd, out_char, 1)");

  errno = 0;
  // fd not OK, buffer OK, count OK
  ret_val = read(-1, out_char, 1);
  if (ret_val != -1)
    return failed(testname, "read(-1, out_char, 1)");
  // bad file number
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");

  errno = 0;
  // fd OK, buffer OK, count not OK
  // Linux's read() (unsandboxed) does not reject this buffer size.
  if (!NONSFI_MODE) {
    ret_val = read(fd, out_char, -1);
    if (ret_val != -1)
      return failed(testname, "read(fd, out_char, -1)");
    // bad address
    ASSERT_EQ(errno, EFAULT);
    if (EFAULT != errno)
      return failed(testname, "EFAULT != errno");
  }

  errno = 0;
  // fd not OK, buffer OK, count not OK
  ret_val = read(-1, out_char, -1);
  if (ret_val != -1)
    return failed(testname, "read(-1, out_char, -1)");
  // bad descriptor
  if (NONSFI_MODE) {
    // Under qemu-arm, this read() call returns EFAULT.
    if (EBADF != errno && EFAULT != errno)
      return failed(testname, "errno is not EBADF or EFAULT");
  } else {
    if (EBADF != errno)
      return failed(testname, "EBADF != errno");
  }

  // fd OK, buffer OK, count 0
  ret_val = read(fd, out_char, 0);
  if (ret_val != 0)
    return failed(testname, "read(fd, out_char, 0)");

  // read 10, but only 3 are left
  ret_val = read(fd, out_char, 10);
  if (ret_val != 4)
    return failed(testname, "read(fd, out_char, 10)");

  // EOF
  ret_val = read(fd, out_char, 10);
  if (ret_val != 0)
    return failed(testname, "read(fd, out_char, 10)");

  close(fd);
  return passed(testname, "all");
}

// write() returns the number of bytes written on success, -1 on error
bool test_write(const char *test_file) {
  int fd;
  int ret_val;
  char out_char[] = "12";
  const char *testname = "test_write";

  fd = open(test_file, O_WRONLY);
  if (fd == -1)
    return failed(testname, "open(test_file, O_WRONLY)");

  // all params OK
  ret_val = write(fd, out_char, 2);
  if (ret_val != 2)
    return failed(testname, "write(fd, out_char, 2)");

  errno = 0;
  // invalid count
  // Linux's write() (unsandboxed) does not reject this buffer size.
  if (!NONSFI_MODE) {
    ret_val = write(fd, out_char, -1);
    if (ret_val != -1)
      return failed(testname, "write(fd, out_char, -1)");
    // bad address
    if (EFAULT != errno)
      return failed(testname, "EFAULT != errno");
  }

  errno = 0;
  // invalid fd
  ret_val = write(-1, out_char, 2);
  if (ret_val != -1)
    return failed(testname, "write(-1, out_char, 2)");
  // bad address
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");

  close(fd);
  return passed(testname, "all");
}

// lseek returns the resulting offset location in bytes from the
// beginning of the file, -1 on error
bool test_lseek(const char *test_file) {
  int fd;
  int ret_val;
  char out_char;
  const char *testname = "test_lseek";

  fd = open(test_file, O_RDWR);
  if (fd == -1)
    return failed(testname, "open(test_file, O_RDWR)");

  ret_val = lseek(fd, 2, SEEK_SET);
  if (ret_val != 2)
    return failed(testname, "lseek(fd, 2, SEEK_SET)");

  errno = 0;
  ret_val = lseek(-1, 1, SEEK_SET);
  if (ret_val != -1)
    return failed(testname, "lseek(-1, 1, SEEK_SET)");
  // bad file number
  if (EBADF != errno)
    return failed(testname, "EBADF != errno");

  ret_val = read(fd, &out_char, 1);
  if ((ret_val != 1) || (out_char != '3'))
    return failed(testname, "read(fd, &out_char, 1) #1");

  ret_val = lseek(fd, 1, SEEK_CUR);
  if (ret_val != 4)
    return failed(testname, "lseek(fd, 1, SEEK_CUR)");

  ret_val = read(fd, &out_char, 1);
  if ((ret_val != 1) || (out_char != '5'))
    return failed(testname, "read(fd, &out_char, 1) #2");

  ret_val = lseek(fd, -1, SEEK_CUR);
  if (ret_val != 4)
    return failed(testname, "lseek(fd, -1, SEEK_CUR)");

  ret_val = read(fd, &out_char, 1);
  if ((ret_val != 1) || (out_char != '5'))
    return failed(testname, "read(fd, &out_char, 1) #3");

  ret_val = lseek(fd, -2, SEEK_END);
  if (ret_val != 3)
    return failed(testname, "lseek(fd, -2, SEEK_END)");

  ret_val = read(fd, &out_char, 1);
  if ((ret_val != 1) || (out_char != '4'))
    return failed(testname, "read(fd, &out_char, 1) #4");

  ret_val = lseek(fd, 4, SEEK_END);
  // lseek allows for positioning beyond the EOF
  if (ret_val != 9)
    return failed(testname, "lseek(fd, 4, SEEK_END)");

  ret_val = lseek(fd, 4, SEEK_SET);
  if (ret_val != 4)
    return failed(testname, "lseek(fd, 4, SEEK_SET)");

  errno = 0;
  ret_val = lseek(fd, 4, SEEK_END + 3);
  if (ret_val != -1)
    return failed(testname, "lseek(fd, 4, SEEK_END + 3)");
  // invalid argument
  if (EINVAL != errno)
    return failed(testname, "EINVAL != errno");

  errno = 0;
  ret_val = lseek(fd, -40, SEEK_SET);
  if (ret_val != -1)
    return failed(testname, "lseek(fd, -40, SEEK_SET)");
  // invalid argument
  if (EINVAL != errno)
    return failed(testname, "EINVAL != errno");

  ret_val = read(fd, &out_char, 1);
  if ((ret_val != 1) || (out_char == '4'))
    return failed(testname, "read(fd, &out_char, 1) #5");

  close(fd);
  return passed(testname, "all");
}

bool test_readdir(const char *test_file) {
  // TODO(mseaborn): Implement listing directories for unsandboxed mode.
  if (NONSFI_MODE)
    return true;

  // Read the directory containing the test file

  // Split filename into basename and dirname.
  char dirname[PATH_MAX];
  strncpy(dirname, test_file, PATH_MAX);
  char *basename = split_name(dirname);

  // Read the directory listing and verify that the test_file is
  // present.
  int found = 0;
  DIR *d = opendir(dirname);
  ASSERT_NE_MSG(d, NULL, "opendir failed");
  int count = 0;
  struct dirent *ent;
  while (1) {
    ent = readdir(d);
    if (!ent)
      break;
    if (!strcmp(ent->d_name, basename))
      found = 1;
    count++;
  }
  ASSERT_EQ_MSG(1, found, "failed to find test file in directory listing");

  // Rewind directory and verify that the number of elements
  // matches the previous count.
  rewinddir(d);
  while (readdir(d))
    count--;
  ASSERT_EQ_MSG(0, count, "readdir after rewinddir was inconsistent");

  ASSERT_EQ(0, closedir(d));
  return passed("test_readdir", "all");
}

// isatty returns 1 for TTY descriptors and 0 on error (setting errno)
bool test_isatty(const char *test_file) {
  // TODO(mseaborn): Implement isatty() for unsandboxed mode.
  // We need to write two if-statements two avoid clang's warning.
  if (NONSFI_MODE)
    if (TESTS_USE_IRT)
      return true;

  // TODO(sbc): isatty() in glibc is not yet hooked up to the IRT
  // interfaces. Remove this conditional once this gets addressed:
  // https://code.google.com/p/nativeclient/issues/detail?id=3709
#if defined(__GLIBC__)
  return true;
#endif

  // Open a regular file that check that it is not a tty.
  int fd = open(test_file, O_RDONLY);
  ASSERT_NE_MSG(fd, -1, "open() failed");
  errno = 0;
  ASSERT_EQ_MSG(isatty(fd), 0, "isatty returned non-zero");
  ASSERT_EQ_MSG(errno, ENOTTY, "isatty failed to set errno to ENOTTY");
  close(fd);

  // Verify that isatty() on closed file returns 0 and sets errno to EBADF
  errno = 0;
  ASSERT_EQ_MSG(isatty(fd), 0, "isatty returned non-zero");
  ASSERT_EQ_MSG(errno, EBADF, "isatty failed to set errno to EBADF");

  // On Linux opening /dev/ptmx always returns a TTY file descriptor.
  fd = open("/dev/ptmx", O_RDWR);
  if (fd >= 0) {
    errno = 0;
    ASSERT_EQ(isatty(fd), 1);
    ASSERT_EQ(errno, 0);
    close(fd);
  }

  return passed("test_isatty", "all");
}

/*
 * Not strictly speaking a syscall, but we have a 'fake' implementation
 * that we want to test.
 */
bool test_gethostname() {
  char hostname[256];
  ASSERT_EQ(gethostname(hostname, 1), -1);
#ifdef __GLIBC__
  // glibc only provides a stub gethostbyname() that returns
  // ENOSYS in all cases.
  ASSERT_EQ(errno, ENOSYS);
#else
  ASSERT_EQ(errno, ENAMETOOLONG);

  errno = 0;
  ASSERT_EQ(gethostname(hostname, 256), 0);
  ASSERT_EQ(errno, 0);
  ASSERT_EQ(strcmp(hostname, "naclhost"), 0);
#endif
  return passed("test_gethostname", "all");
}

/*
 * function testSuite()
 *
 *   Run through a complete sequence of file tests.
 *
 * returns true if all tests succeed.  false if one or more fail.
 */

bool testSuite(const char *test_file) {
  bool ret = true;
  // The order of executing these tests matters!
  ret &= test_sched_yield();
  ret &= test_sysconf();
  ret &= test_stat(test_file);
  ret &= test_open(test_file);
  ret &= test_close(test_file);
  ret &= test_read(test_file);
  ret &= test_write(test_file);
  ret &= test_lseek(test_file);
  ret &= test_readdir(test_file);
  ret &= test_gethostname();
// glibc support for calling syscalls directly, without the IRT, is limited
// so we skip certain tests in this case.
#if !defined(__GLIBC__) || TESTS_USE_IRT
  ret &= test_unlink(test_file);
  ret &= test_chdir();
  ret &= test_mkdir_rmdir(test_file);
  ret &= test_getcwd();
  ret &= test_mkdir_rmdir(test_file);
  ret &= test_isatty(test_file);
  ret &= test_rename(test_file);
  ret &= test_link(test_file);
  if (!NONSFI_MODE) {
    ret &= test_symlinks(test_file);
  }
  ret &= test_chmod(test_file);
  ret &= test_access(test_file);
#endif
// TODO(sbc): remove this restriction once glibc's truncate calls
// is hooked up to the IRT dev-filename-0.2 interface:
// https://code.google.com/p/nativeclient/issues/detail?id=3709
#if !defined(__GLIBC__)
  ret &= test_truncate(test_file);
#endif
  ret &= test_utimes(test_file);
  return ret;
}

/*
 * main entry point.
 *
 * run all tests and call system exit with appropriate value
 *   0 - success, all tests passed.
 *  -1 - one or more tests failed.
 */

int main(const int argc, const char *argv[]) {
  bool passed;

  if (argc != 2) {
    printf("Please specify the test file name\n");
    exit(-1);
  }
  // run the full test suite
  passed = testSuite(argv[1]);

  if (passed) {
    printf("All tests PASSED\n");
    exit(0);
  } else {
    printf("One or more tests FAILED\n");
    exit(-1);
  }
}
