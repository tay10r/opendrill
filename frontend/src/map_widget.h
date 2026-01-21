#pragma once

namespace opendrill {

[[nodiscard]] auto
begin_map_widget(const char* label, bool crosshairs) -> bool;

void
end_map_widget();

} // namespace opendrill
