/*
 * Copyright (c) 2011 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_SIMPLE_SERVICE_NACL_SIMPLE_RSERVICE_H_
#define NATIVE_CLIENT_SRC_TRUSTED_SIMPLE_SERVICE_NACL_SIMPLE_RSERVICE_H_

#include "native_client/src/include/nacl_base.h"

#include "native_client/src/shared/platform/nacl_threads.h"
#include "native_client/src/trusted/nacl_base/nacl_refcount.h"

/*
 * Reverse service channels.
 */

#include "native_client/src/trusted/simple_service/nacl_simple_service.h"
/* NaClSimpleServiceConnection */

EXTERN_C_BEGIN

/*
 * A reverse service client accepts connections and then invokes a
 * closure -- |client_callback| with a state variable |data| -- to
 * allow the instance to perform RPCs to the server side.  The RPC
 * server is a class the objects of which have a
 * |ConnectAndSpawnHandler| method to spawn a thread which connects to
 * the NaClSimpleRevServiceClient, and then becomes a service thread.
 */
struct NaClSimpleRevClient {
  struct NaClRefCount base NACL_IS_REFCOUNT_SUBCLASS;
  struct NaClDesc     *bound_and_cap[2];

  int                 acceptor_spawned;
  struct NaClThread   acceptor;

  /*
   * The client_callback is invoked on the |acceptor| thread.
   * Typically, this callback will simply pass the received |conn|
   * connection to the actual RPC client code that's waitng for the
   * connected channel, perhaps via synchronization mechanisms hanging
   * off of |data|.  The |client_callback| is not expected to block.
   * If the user code needs to actually run some sequence of RPCs, it
   * should spawn a new thread to do so, lest no other clients can
   * make connections.
   */
  void                (*client_callback)(
      void                        *state,
      struct NaClDesc             *conn);
  void                *state;
};

struct NaClSimpleRevClientVtbl {
  struct NaClRefCountVtbl   vbase;
};

extern struct NaClSimpleRevClientVtbl const kNaClSimpleRevClientVtbl;

int NaClSimpleRevClientCtor(struct NaClSimpleRevClient  *self,
                            void                        (*callback)(
                                void                        *state,
                                struct NaClDesc             *conn),
                            void                        *state);

int NaClSimpleRevClientStartServiceThread(struct NaClSimpleRevClient *client);

/*
 * The RPC server is the IMC client.  The reverse service connection
 * is initiated by this object via the |ConnectAndSpawnHandler|
 * method, which makes a connection to the IMC server / RPC client.
 */
struct NaClSimpleRevService {
  struct NaClRefCount               base NACL_IS_REFCOUNT_SUBCLASS;

  struct NaClDesc                   *conn_cap;

  struct NaClSrpcHandlerDesc const  *handlers;
};

/*
 * A NaClSimpleRevService object is an RPC client.  Thus, it holds
 * both a connection capability and the RPC service routines, and has
 * a function for initiating the IMC connection, which spawns a RPC
 * service thread that (typically) services the connected socket until
 * the connection is closed.  When the service thread is created, it
 * holds a reference to the NaClSimpleRevService object.
 */
int NaClSimpleRevServiceCtor(struct NaClSimpleRevService      *self,
                             struct NaClDesc                  *conn_cap,
                             struct NaClSrpcHandlerDesc const *handlers);

void NaClSimpleRevServiceDtor(struct NaClRefCount *vself);

/*
 * A NaClSimpleRevServiceConnection is essentially isomorphic to a
 * NaClSimpleServiceConnection, except it contains a back pointer to
 * NaClSimpleRevService rather than a NaClSimpleService.
 */
struct NaClSimpleRevConnection;

struct NaClSimpleRevServiceVtbl {
  struct NaClRefCountVtbl     vbase;

  /* syscall convention */
  int                         (*ConnectAndSpawnHandler)(
      struct NaClSimpleRevService *self,
      void                        *instance_data,
      void                        (*instance_data_cleanup)(
          void *instance_data));

  /* syscall convention */
  int                         (*RevConnectionFactory)(
      struct NaClSimpleRevService     *self,
      struct NaClDesc                 *conn,
      void                            *instance_data,
      void                            (*instance_data_cleanup)(
          void *instance_data),
      struct NaClSimpleRevConnection  **out);

  void                        (*RpcHandler)(
      struct NaClSimpleRevService     *self,
      struct NaClSimpleRevConnection *conn);
};

extern struct NaClSimpleRevServiceVtbl const kNaClSimpleRevServiceVtbl;

struct NaClSimpleRevConnection {
  struct NaClRefCount         base NACL_IS_REFCOUNT_SUBCLASS;
  struct NaClSimpleRevService *service;           /* holds a ref */
  struct NaClDesc             *connected_socket;  /* holds a ref */
  struct NaClThread           thread;

  void                        *instance_data;
  void                        (*instance_data_cleanup)(void *instance_data);
};

int NaClSimpleRevConnectionCtor(
    struct NaClSimpleRevConnection  *self,
    struct NaClSimpleRevService     *service,
    struct NaClDesc                 *conn,
    void                            *instance_data,
    void                            (*instance_data_cleanup)(
        void *instance_data));

void NaClSimpleRevConnectionDtor(struct NaClRefCount *vself);

int NaClSimpleRevServiceConnectionFactory(
    struct NaClSimpleRevService     *self,
    struct NaClDesc                 *conn,
    void                            *instance_data,
    void                            (*instance_data_cleanup)(
        void *instance_data),
    struct NaClSimpleRevConnection  **out);

extern struct NaClRefCountVtbl kNaClSimpleRevConnectionVtbl;

EXTERN_C_END

#endif
