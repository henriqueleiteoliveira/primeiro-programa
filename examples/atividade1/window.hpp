#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaintUI() override;

private:
  static int const m_N{16}; // Board size is m_N x m_N

  bool m_XsTurn{true};
  std::array<char, m_N * m_N> m_board{}; // '\0', '1' or '2'

  void newGame();
};

#endif