#pragma once

#include "tool.h"

#include <vector>

namespace opendrill {

class drill;

class line_tool final : public tool
{
public:
  void render_menu(tool_api&) override;

  void render_plot(tool_api&) override;

  [[nodiscard]] auto label() const -> const char* override { return "Line Tool"; }

protected:
  void apply(drill& d);

private:
  int positions_{ 5 };

  float interval_{ 2.0F };

  std::vector<float> x_buffer_;

  std::vector<float> y_buffer_;
};

} // namespace opendrill
