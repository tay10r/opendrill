#include <glow/main.hpp>

#include "drill.h"
#include "map_widget.h"
#include "tool.h"

#include "line_tool.h"

#include <memory>

namespace opendrill {

namespace {

class app_impl final
  : public glow::app
  , public tool_api
{
public:
  void setup(glow::platform&) override
  {
    //
  }

  void teardown(glow::platform&) override
  {
    //
  }

  void loop(glow::platform&) override
  {
    auto y_offset = 0;

    if (ImGui::BeginMainMenuBar()) {

      render_main_menu_bar();

      y_offset = ImGui::GetWindowSize().y;

      ImGui::EndMainMenuBar();
    }

    auto& io = ImGui::GetIO();

    const auto ds = io.DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(0, y_offset), ImGuiCond_Always);

    ImGui::SetNextWindowSize(ImVec2(ds.x, ds.y - y_offset), ImGuiCond_Always);

    ImGui::Begin("##mainwindow", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);

    render_main_window();

    ImGui::End();

    if (tool_) {

      render_tool_widget(*tool_, io.DisplaySize);
    }
  }

protected:
  void render_tool_widget(tool& t, const ImVec2& displaySize)
  {
    const auto margin{ 32.0F };
    const auto w{ 256 };
    const auto h{ 192 };

    ImGui::SetNextWindowPos(ImVec2(margin, displaySize.y - margin - h), ImGuiCond_FirstUseEver);

    ImGui::SetNextWindowSize(ImVec2(w, h));

    if (ImGui::Begin(t.label())) {
      tool_->render_menu(*this);
    }

    ImGui::End();
  }

  void render_main_window()
  {
    if (begin_map_widget("##map", !!tool_)) {

      if (tool_) {
        tool_->render_plot(*this);
      }

      end_map_widget();
    }
  }

  void render_main_menu_bar()
  {
    if (ImGui::Button("L")) {
      tool_.reset(new line_tool());
    }
  }

protected: // tool API
  [[nodiscard]] auto get_drill() const -> const drill& override { return drill_; }

  [[nodiscard]] auto begin_drill_edit() -> drill* override { return &drill_; }

  void end_drill_edit() override
  {
    // TODO
  }

private:
  std::unique_ptr<tool> tool_;

  drill drill_;
};

} // namespace

} // namespace opendrill

GLOW_APP(opendrill::app_impl);
