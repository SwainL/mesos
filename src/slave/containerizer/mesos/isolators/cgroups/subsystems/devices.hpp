// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __CGROUPS_ISOLATOR_SUBSYSTEMS_DEVICES_HPP__
#define __CGROUPS_ISOLATOR_SUBSYSTEMS_DEVICES_HPP__

#include <string>
#include <vector>

#include <process/owned.hpp>

#include <stout/hashset.hpp>
#include <stout/try.hpp>

#include "linux/cgroups.hpp"

#include "slave/flags.hpp"

#include "slave/containerizer/mesos/isolators/cgroups/constants.hpp"
#include "slave/containerizer/mesos/isolators/cgroups/subsystem.hpp"

namespace mesos {
namespace internal {
namespace slave {

/**
 * Represent cgroups devices subsystem.
 */
class DevicesSubsystem: public Subsystem
{
public:
  static Try<process::Owned<Subsystem>> create(
      const Flags& flags,
      const std::string& hierarchy);

  ~DevicesSubsystem() override = default;

  std::string name() const override
  {
    return CGROUP_SUBSYSTEM_DEVICES_NAME;
  }

  process::Future<Nothing> prepare(
      const ContainerID& containerId,
      const std::string& cgroup) override;

  process::Future<Nothing> recover(
      const ContainerID& containerId,
      const std::string& cgroup) override;

  process::Future<Nothing> cleanup(
      const ContainerID& containerId,
      const std::string& cgroup) override;

private:
  DevicesSubsystem(
      const Flags& flags,
      const std::string& hierarchy,
      const std::vector<cgroups::devices::Entry>& whitelistDeviceEntries);

  hashset<ContainerID> containerIds;
  std::vector<cgroups::devices::Entry> whitelistDeviceEntries;
};

} // namespace slave {
} // namespace internal {
} // namespace mesos {

#endif // __CGROUPS_ISOLATOR_SUBSYSTEMS_DEVICES_HPP__
