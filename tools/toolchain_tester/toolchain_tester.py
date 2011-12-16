#!/usr/bin/python
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Simple test suite for toolchains espcially llvm arm toolchains.

Sample invocations

tools/toolchain_tester/toolchain_tester.py  [options]+ test1.c test2.c ...

where options are

--config <config>
--append <tag>=<value>
--verbose
--show_console
--exclude=<filename>
--tmp=<path>
--check_excludes
--concurrency=<number>

e.g. --append "CFLAGS:-lsupc++" will enable C++ eh support

NOTE: the location of tmp files is intentionally hardcoded, so you
can only run one instance of this at a time.
"""


import getopt
import glob
import os
import shlex
import subprocess
import sys
import threading
import time

import toolchain_config
# ======================================================================
# Options
# ======================================================================
# list of streams being logged to (both normal and verbose output)
REPORT_STREAMS = [sys.stdout]
# max time (secs) to wait for command any command to complete
TIMEOUT = 120
# enable verbose output, e.g. commands being executed
VERBOSE = 0
# prefix for temporary files
TMP_PREFIX = '/tmp/tc_test_'
# show command output (stdout/stderr)
SHOW_CONSOLE = 1
# append these settings to config
APPEND = []
# exclude these tests
EXCLUDE = {}
# check whether excludes are still necessary
CHECK_EXCLUDES = 0
# module with settings for compiler, etc.
CFG = None

CONCURRENCY = 1
ERRORS_LOCK = threading.Lock()
NUM_ERRORS = 0
# ======================================================================
# Hook print to we can print to both stdout and a file
def Print(message):
  for s in REPORT_STREAMS:
    print >>s, message


# ======================================================================
def Banner(message):
  Print('=' * 70)
  Print(message)
  Print('=' * 70)

# ======================================================================
def RunCommand(cmd, always_dump_stdout_stderr):
  """Run a shell command given as an argv style vector."""
  if VERBOSE:
    Print(str(cmd))
    Print(" ".join(cmd))
  start = time.time()
  p = subprocess.Popen(cmd,
                       bufsize=1000*1000,
                       stderr=subprocess.PIPE,
                       stdout=subprocess.PIPE)
  while p.poll() is None:
    time.sleep(0.1)
    now = time.time()
    if now - start > TIMEOUT:
      Print('Error: timeout')
      Print('Killing pid %d' % p.pid)
      os.waitpid(-1, os.WNOHANG)
      return -1
  stdout = p.stdout.read()
  stderr = p.stderr.read()
  retcode = p.wait()

  if retcode != 0:
    Print('Error: command failed %d %s' % (retcode, str(cmd)))
    always_dump_stdout_stderr = True

  if always_dump_stdout_stderr:
    Print(stderr)
    Print(stdout)
  return retcode


def RemoveTempFiles():
  global TMP_PREFIX
  for f in glob.glob(TMP_PREFIX + '*'):
    os.remove(f)


def MakeExecutableCustom(config, test, extra):
  global TMP_PREFIX
  global SHOW_CONSOLE
  d = extra.copy()
  d['tmp'] = TMP_PREFIX + '_' + os.path.basename(test)
  d['src'] = test
  for phase, command in config.GetCommands(d):
    command = shlex.split(command)
    try:
      retcode = RunCommand(command, SHOW_CONSOLE)
    except Exception, err:
      Print("cannot run phase %s: %s" % (phase, str(err)))
      return phase
    if retcode:
      return phase
  # success
  return ''


def ParseCommandLineArgs(argv):
  """Process command line options and return the unprocessed left overs."""
  global VERBOSE, COMPILE_MODE, RUN_MODE, TMP_PREFIX
  global CFG, APPEND, SHOW_CONSOLE, CHECK_EXCLUDES, CONCURRENCY
  try:
    opts, args = getopt.getopt(argv[1:], '',
                               ['verbose',
                                'show_console',
                                'append=',
                                'config=',
                                'exclude=',
                                'check_excludes',
                                'tmp=',
                                'concurrency='])
  except getopt.GetoptError, err:
    Print(str(err))  # will print something like 'option -a not recognized'
    sys.exit(-1)

  for o, a in opts:
    # strip the leading '--'
    o = o[2:]
    if o == 'verbose':
      VERBOSE = 1
    elif o == 'show_console':
      SHOW_CONSOLE = 1
    elif o == 'check_excludes':
      CHECK_EXCLUDES = 1
    elif o == 'tmp':
      TMP_PREFIX = a
    elif o == 'exclude':
      f = open(a)
      for line in f:
        line = line.strip()
        if not line: continue
        if line.startswith('#'): continue
        if line in EXCLUDE:
          Print('ERROR: duplicate exclude: [%s]' % line)
        EXCLUDE[line] = a
      f.close()
      Print('Size of excludes now: %d' % len(EXCLUDE))
    elif o == 'append':
      tag, value = a.split(":", 1)
      APPEND.append((tag, value))
    elif o == 'config':
      CFG = a
    elif o == 'concurrency':
      CONCURRENCY = int(a)
    else:
      Print('ERROR: bad commandline arg: %s' % o)
      sys.exit(-1)
    # return the unprocessed options, i.e. the command
  return args


def RunTest(sema, config, test, extra_flags, errors):
  global ERRORS_LOCK, NUM_ERRORS
  try:
    result = MakeExecutableCustom(config, test, extra_flags)
    if result:
      Print('Failure %s: %s' % (result, test))
      ERRORS_LOCK.acquire()
      errors[result].append(test)
      NUM_ERRORS += 1
      ERRORS_LOCK.release()
  finally:
    # ensure the main thread doesn't block even if there's an error here
    sema.release()


def RunSuite(config, files, extra_flags, errors):
  """Run a collection of benchmarks."""
  global NUM_ERRORS, CONCURRENCY
  NUM_ERRORS = sum(len(errors[k]) for k in errors)
  Banner('running %d tests' % (len(files)))
  sema = threading.Semaphore(CONCURRENCY)
  for num, test in enumerate(files):
    threadargs = (sema, config, test, extra_flags, errors)
    t = threading.Thread(target=RunTest, name=test, args=threadargs)
    t.daemon = True # ensure program will exit when the main thread exits
    sema.acquire()
    Print('Running %03d/%03d: %s (%d errors so far)' %
          (num, len(files), os.path.basename(test), NUM_ERRORS))
    t.start()


def FilterOutExcludedTests(files, exclude):
  return  [f for f in files if not os.path.basename(f) in exclude]


def main(argv):
  files = ParseCommandLineArgs(argv)

  if not CFG:
    print 'ERROR: you must specify a toolchain-config using --config=<config>'
    print 'Available configs are: '
    print '\n'.join(toolchain_config.TOOLCHAIN_CONFIGS.keys())
    print
    return -1

  global TMP_PREFIX
  global APPEND
  TMP_PREFIX = TMP_PREFIX + CFG

  Banner('Config: %s' % CFG)
  config = toolchain_config.TOOLCHAIN_CONFIGS[CFG]
  for tag, value in APPEND:
    config.Append(tag, value)
  config.SanityCheck()
  Print('TMP_PREFIX: %s' % TMP_PREFIX)

  # initialize error stats
  errors = {}
  for phase in config.GetPhases():
    errors[phase] = []

  Print('Tests before filtering %d' % len(files))
  if not CHECK_EXCLUDES:
    files = FilterOutExcludedTests(files, EXCLUDE)
  Print('Tests after filtering %d' % len(files))
  try:
    RunSuite(config, files, {}, errors)
  finally:
    RemoveTempFiles()

  # print error report
  USED_EXCLUDES = {}
  num_errors = 0
  for k in errors:
    lst = errors[k]
    if not lst: continue
    Banner('%d failures in phase %s' % (len(lst), k))
    for e in lst:
      if os.path.basename(e) in EXCLUDE:
        USED_EXCLUDES[os.path.basename(e)] = None
        continue
      Print(e)
      num_errors += 1

  if CHECK_EXCLUDES:
    Banner('Unnecessary excludes:')
    for e in EXCLUDE:
      if e not in USED_EXCLUDES:
        Print(e + ' (' + EXCLUDE[e] + ')')
  return num_errors > 0

if __name__ == '__main__':
  sys.exit(main(sys.argv))
