#include "line_tool.h"

#include "drill.h"

#include <imgui.h>

#include <implot.h>

namespace opendrill {

void
line_tool::render_plot(tool_api& api)
{
  if (positions_ <= 0) {
    return;
  }

  x_buffer_.resize(static_cast<size_t>(positions_));
  y_buffer_.resize(static_cast<size_t>(positions_));

  // TODO : handle rotation

  const auto mouse_pos = ImPlot::GetPlotMousePos();

  const auto min_v = -static_cast<float>(positions_ - 1) * interval_ * 0.5F;

  for (int i = 0; i < positions_; i++) {
    x_buffer_[i] = mouse_pos.x + min_v + interval_ * static_cast<float>(i);
    y_buffer_[i] = mouse_pos.y;
  }

  ImPlot::PlotScatter("##line_tool", x_buffer_.data(), y_buffer_.data(), positions_);

  if (ImPlot::IsPlotHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    api.edit_drill([this](drill* d) { apply(*d); });
  }
}

void
line_tool::render_menu(tool_api&)
{
  ImGui::InputInt("Positions", &positions_);

  ImGui::InputFloat("Interval", &interval_);
}

void
line_tool::apply(drill& d)
{
  for (int i = 0; i < positions_; i++) {

    auto [route_id, r] = d.routes.add();

    auto [perf_id, p] = d.performers.add();

    p->route_id = route_id;

    auto [waypoint_id, wp] = d.waypoints.add();

    wp->route_id = route_id;

    // TODO
    wp->time = 0;
    wp->x = 0;
    wp->y = 0;
  }
}

} // namespace opendrill
