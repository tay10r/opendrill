#pragma once

#include <iosfwd>
#include <vector>

#include <cstdint>

namespace opendrill {

using pk_uint32 = std::uint32_t;

template<typename T>
struct table final
{
  pk_uint32 next_id{ 1 };

  std::vector<std::pair<pk_uint32, T>> rows;

  [[nodiscard]] auto add() -> std::pair<pk_uint32, T*>
  {
    rows.emplace_back(next_id, T{});

    ++next_id;

    return std::make_pair(next_id - 1, &rows.back().second);
  }
};

struct waypoint final
{
  pk_uint32 route_id;

  float time{ 0 };

  float x{ 0 };

  float y{ 0 };
};

struct route final
{};

struct performer final
{
  pk_uint32 route_id{ 0 };
};

struct drill final
{
  table<performer> performers;

  table<route> routes;

  table<waypoint> waypoints;

  void save(std::ostream& out) const;
};

} // namespace opendrill
