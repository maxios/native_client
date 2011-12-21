#!/bin/bash
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
#@ This script for up/downloading native client toolchains.

#set -o xtrace
set -o nounset
set -o errexit

######################################################################
# Helper
######################################################################

Banner() {
  echo "######################################################################"
  echo $*
  echo "######################################################################"
}


Usage() {
  egrep "^#@" $0 | cut --bytes=3-
}

SanityCheck() {
  Banner "Sanity Checks"
  if [[ $(basename $(pwd)) != "native_client" ]] ; then
    echo "ERROR: run this script from the native_client/ dir"
    exit -1
  fi
}

######################################################################
# Config
######################################################################

readonly GS_UTIL=${GS_UTIL:-buildbot/gsutil.sh}

readonly URL_PREFIX=https://commondatastorage.googleapis.com

readonly BASE_ARM_TOOLCHAIN=nativeclient-archive2/toolchain

readonly BASE_BETWEEN_BOTS_TRY=nativeclient-trybot/between_builders
readonly BASE_BETWEEN_BOTS=nativeclient-archive2/between_builders


######################################################################
# UTIL
######################################################################
Upload() {
  echo  "uploading: $2"
  ${GS_UTIL} -h Cache-Control:no-cache cp -a public-read $1 $2
}


UploadArmToolchain() {
  rev=$1
  name=$2
  tarball=$3

  Upload ${tarball} gs://${BASE_ARM_TOOLCHAIN}/${rev}/${name}
}

######################################################################
# ARM TRUSTED
######################################################################

UploadArmTrustedToolchain() {
  rev=$1
  tarball=$2

  UploadArmToolchain ${rev} naclsdk_linux_arm-trusted.tgz ${tarball}
}

DownloadArmTrustedToolchain() {
  local rev=$1
  local tarball=$2
  curl -L \
     ${URL_PREFIX}/${BASE_ARM_TOOLCHAIN}/${rev}/naclsdk_linux_arm-trusted.tgz
     -o $2
}

ShowRecentArmTrustedToolchains() {
   local url=gs://${BASE_ARM_TOOLCHAIN}/*/naclsdk_linux_arm-trusted.tgz
   local recent=$(${GS_UTIL} ls ${url} | tail -5)
   for url in ${recent} ; do
     if ${GS_UTIL} ls -L "${url}" ; then
       echo "====="
     fi
   done
}

######################################################################
# ARM UN-TRUSTED
######################################################################

#@ label should be in :
#@
#@ pnacl_linux_i686_newlib
#@ pnacl_linux_i686_glibc
#@ pnacl_linux_x86_64_newlib
#@ pnacl_linux_x86_64_glibc
#@ pnacl_darwin_i386_newlib
#@ pnacl_darwin_i386_glibc
#@ pnacl_windows_i686_newlib
#@ pnacl_windows_i686_newlib

UploadArmUntrustedToolchains() {
  local rev=$1
  local label=$2
  local tarball=$3

  UploadArmToolchain ${rev} naclsdk_${label}.tgz ${tarball}
}

DownloadArmUntrustedToolchains() {
  local rev=$1
  local label=$2
  local tarball=$3

   curl -L \
     ${URL_PREFIX}/${BASE_ARM_TOOLCHAIN}/${rev}/naclsdk_${label}.tgz
     -o $2
}

ShowRecentArmUntrustedToolchains() {
  local label=$1
  local url="gs://${BASE_ARM_TOOLCHAIN}/*/naclsdk_${label}.tgz"

  local recent=$(${GS_UTIL} ls ${url} | tail -5)
  for url in ${recent} ; do
    if ${GS_UTIL} ls -L "${url}" ; then
      echo "====="
    fi
  done
}

######################################################################
# ARM BETWEEN BOTS
######################################################################

UploadArmBinariesForHWBots() {
  name=$1
  tarball=$2
  Upload ${tarball} ${BASE_BETWEEN_BOTS}/${name}/build.tgz
}


DownloadArmBinariesForHWBots() {
  name=$1
  tarball=$2
  curl -L \
     ${URL_PREFIX}/${BASE_BETWEEN_BOTS}/${name}/build.tgz \
     -o ${tarball}
}

######################################################################
# ARM BETWEEN BOTS TRY
######################################################################

UploadArmBinariesForHWBotsTry() {
  name=$1
  tarball=$2
  Upload ${tarball} ${BASE_BETWEEN_BOTS_TRY}/${name}/build.tgz
}


DownloadArmBinariesForHWBotsTry() {
  name=$1
  tarball=$2
  curl -L \
     ${URL_PREFIX}/${BASE_BETWEEN_BOTS_TRY}/${name}/build.tgz \
     -o ${tarball}
}

######################################################################
# DISPATCH
######################################################################
SanityCheck

if [[ $# -eq 0 ]] ; then
  echo "you must specify a mode on the commandline:"
  echo
  Usage
  exit -1
elif [[ "$(type -t $1)" != "function" ]]; then
  echo "ERROR: unknown function '$1'." >&2
  echo "For help, try:"
  echo "    $0 help"
  exit 1
else
  "$@"
fi
