// Copyright (c) 2011 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVE_CLIENT_SRC_SHARED_PPAPI_PROXY_BROWSER_GLOBALS_H_
#define NATIVE_CLIENT_SRC_SHARED_PPAPI_PROXY_BROWSER_GLOBALS_H_

#include "ppapi/c/dev/ppb_context_3d_dev.h"
#include "ppapi/c/dev/ppb_context_3d_trusted_dev.h"
#include "ppapi/c/dev/ppb_file_io_dev.h"
#include "ppapi/c/dev/ppb_file_system_dev.h"
#include "ppapi/c/dev/ppb_scrollbar_dev.h"
#include "ppapi/c/dev/ppb_surface_3d_dev.h"
#include "ppapi/c/dev/ppb_var_deprecated.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppb_core.h"
#include "ppapi/c/ppb_graphics_2d.h"
#include "ppapi/c/ppb_image_data.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppb_url_loader.h"
#include "ppapi/c/ppb_url_request_info.h"
#include "ppapi/c/ppb_url_response_info.h"
#include "ppapi/c/trusted/ppb_image_data_trusted.h"

struct NaClSrpcRpc;
struct NaClSrpcChannel;

namespace ppapi_proxy {

// These functions handle the browser-side (trusted code) mapping of a browser
// Instance to instance-specific data, such as the SRPC communication channel.
// These functions are called by the in-browser (trusted) plugin code, and are
// always called from the main (foreground, UI, ...) thread. As such, they are
// not thread-safe (they do not need to be).

// BrowserPpp keeps browser side PPP_Instance specific information, such as the
// channel used to talk to the instance.
class BrowserPpp;

// Associate a particular BrowserPpp with a PP_Instance value.  This allows the
// browser side to look up information it needs to communicate with the stub.
void SetBrowserPppForInstance(PP_Instance instance,
                              BrowserPpp* browser_ppp);
// When an instance is destroyed, this is called to remove the association, as
// the stub will be destroyed by a call to Shutdown.
void UnsetBrowserPppForInstance(PP_Instance instance);
// Gets the BrowserPpp information remembered for a particular instance.
BrowserPpp* LookupBrowserPppForInstance(PP_Instance instance);

// To keep track of memory allocated by a particular module, we need to remember
// the PP_Module corresponding to a particular NaClSrpcChannel*.
void SetModuleIdForSrpcChannel(NaClSrpcChannel* channel, PP_Module module_id);
// Removes the association with a given channel.
void UnsetModuleIdForSrpcChannel(NaClSrpcChannel* channel);
// Looks up the association with a given channel.
PP_Module LookupModuleIdForSrpcChannel(NaClSrpcChannel* channel);

// Helpers for getting a pointer to the "main channel" for a specific nexe.
NaClSrpcChannel* GetMainSrpcChannel(NaClSrpcRpc* upcall_rpc);
NaClSrpcChannel* GetMainSrpcChannel(PP_Instance);

// Support for getting PPB_ browser interfaces.
// Safe version CHECK's for NULL.
void SetPPBGetInterface(PPB_GetInterface get_interface_function);
const void* GetBrowserInterface(const char* interface_name);
const void* GetBrowserInterfaceSafe(const char* interface_name);
// Functions marked "shared" are to be provided by both the browser and the
// plugin side of the proxy, so they can be used by the shared proxy code
// under both trusted and untrusted compilation.
const PPB_Context3D_Dev* PPBContext3DInterface();
const PPB_Context3DTrusted_Dev* PPBContext3DTrustedInterface();
const PPB_Core* PPBCoreInterface();  // shared
const PPB_FileIO_Dev* PPBFileIOInterface();
const PPB_FileSystem_Dev* PPBFileSystemInterface();
const PPB_Graphics2D* PPBGraphics2DInterface();
const PPB_ImageData* PPBImageDataInterface();
const PPB_ImageDataTrusted* PPBImageDataTrustedInterface();
const PPB_Instance* PPBInstanceInterface();
const PPB_Scrollbar_Dev* PPBScrollbarInterface();
const PPB_Surface3D_Dev* PPBSurface3DInterface();
const PPB_URLLoader* PPBURLLoaderInterface();
const PPB_URLRequestInfo* PPBURLRequestInfoInterface();
const PPB_URLResponseInfo* PPBURLResponseInfoInterface();
const PPB_Var_Deprecated* PPBVarInterface();  // shared

// PPAPI constants used in the proxy.
extern const PP_Resource kInvalidResourceId;

}  // namespace ppapi_proxy

#endif  // NATIVE_CLIENT_SRC_SHARED_PPAPI_PROXY_BROWSER_GLOBALS_H_
