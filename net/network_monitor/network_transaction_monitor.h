/*
* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
*       copyright notice, this list of conditions and the following
*       disclaimer in the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Code Aurora Forum, Inc. nor the names of its
*       contributors may be used to endorse or promote products derived
*       from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
* ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NETWORK_TRANSACTION_MONITOR_H_
#define NETWORK_TRANSACTION_MONITOR_H_

#include "base/basictypes.h"
#include "net/base/host_resolver.h"
#include "net/network_monitor/network_transaction_monitor.h"

#include "net/base/host_resolver_proc.h"
#include "net/base/net_log.h"
#include <string>

namespace network {

class INetworkTransactionMonitor {

public:
   INetworkTransactionMonitor() {};
   virtual ~INetworkTransactionMonitor() {};
   virtual net::HostResolver* CreateHostResolver(size_t max_concurrent_resolves,
                                                 net::HostResolverProc* resolver_proc,
                                                 net::NetLog* net_log, MessageLoop* net_notification_messageloop) = 0;

   virtual void OnIOFailure(net::HostResolver* host, const std::string& connection_group) = 0;
   virtual void OnResourceNotFound(net::HostResolver* host, const net::HostPortPair& host_pair) = 0;

private:
   DISALLOW_COPY_AND_ASSIGN(INetworkTransactionMonitor);
 };

}; //end network

#endif /* NETWORK_TRANSACTION_MONITOR_H_ */