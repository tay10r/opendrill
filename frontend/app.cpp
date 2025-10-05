#include <uikit/main.hpp>

namespace {

class app_impl final : public uikit::app
{
public:
  void setup(uikit::platform&) override {}

  void teardown(uikit::platform&) override {}

  void loop(uikit::platform&) override
  {
    ImGui::DockSpaceOverViewport();

    if (ImGui::BeginMainMenuBar()) {

      render_main_menu_bar();

      ImGui::EndMainMenuBar();
    }

    ImGui::Begin("main");

    ImGui::End();
  }

protected:
  void render_main_menu_bar()
  {
    //
  }
};

} // namespace

UIKIT_APP(app_impl);
