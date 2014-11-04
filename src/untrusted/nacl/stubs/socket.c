/*
 * Copyright 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * Stub routine for `socket' for porting support.
 */

#include <errno.h>

int socket(int domain, int type, int protocol) {
  errno = ENOSYS;
  return -1;
}
