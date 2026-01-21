#pragma once

namespace opendrill {

class drill;

class tool_api
{
public:
  virtual ~tool_api() = default;

  [[nodiscard]] virtual auto get_drill() const -> const drill& = 0;

  template<typename Callback>
  void edit_drill(Callback callback)
  {
    auto* d = begin_drill_edit();
    callback(d);
    end_drill_edit();
  }

protected:
  [[nodiscard]] virtual auto begin_drill_edit() -> drill* = 0;

  virtual void end_drill_edit() = 0;
};

class tool
{
public:
  virtual ~tool() = default;

  virtual void render_menu(tool_api& api) = 0;

  virtual void render_plot(tool_api& api) = 0;

  virtual auto label() const -> const char* = 0;
};

} // namespace opendrill
