#include "map_widget.h"

#include <imgui.h>
#include <implot.h>

namespace opendrill {

[[nodiscard]] auto
begin_map_widget(const char* label, const bool crosshairs) -> bool
{
  auto flags = 0;
  flags |= ImPlotFlags_NoFrame;
  flags |= crosshairs ? ImPlotFlags_Crosshairs : ImPlotFlags_None;

  if (!ImPlot::BeginPlot(label, ImVec2(-1, -1), flags)) {
    return false;
  }

  ImPlot::SetupAxesLimits(-60, 60, -30, 30);

  ImPlot::SetupAxes("", "", ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_NoTickLabels);

  return true;
}

void
end_map_widget()
{
  ImPlot::EndPlot();
}

} // namespace opendrill
