#include "window.hpp"
#include "imgui.h"

void Window::onCreate() {
  newGame();
}

void Window::onPaintUI() {
  // Get size of application's window
  auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
  auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

  // "Atividade 1" window
  {
    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse};
    ImGui::Begin("Desenhe uma Pixel Arte", nullptr, flags);

    // static ImVec4 red_color = {1.0f,0.0f,0.0f,1.0f};
    static ImVec4 white_color = {1.0f,1.0f,1.0f,1.0f};
    // static ImVec4 green_color = {0.0f,0.772f,0.177f,1.0f};
    static ImVec4 gray_color = {0.203f,0.203f,0.203f,1.0f};
    static ImVec4 black_color = {0.0f,0.0f,0.0f,1.0f};

    {
      bool newSelected{};
      if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Arte")) {
          ImGui::MenuItem("Nova Pixel Arte", nullptr, &newSelected);
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }
      if (newSelected) {
        newGame();
      }
    }
    
    // Static text showing current turn or win/draw messages
    {
      std::string text;
      text = fmt::format("Use a cor {}.", m_XsTurn ? "Preta" : "Branca");
      // Center text
      ImGui::SetCursorPosX(
          (appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
      ImGui::Text("%s", text.c_str());
      ImGui::Spacing();
    }

    ImGui::Spacing();

    // Game board
    {
      auto const gridHeight{appWindowHeight - 22 - 60 - (m_N) - 60};
      auto const buttonHeight{gridHeight / m_N};

      if (ImGui::BeginTable("Game board", m_N)) {
        for (auto i : iter::range(m_N)) {
          ImGui::TableNextRow();
          for (auto j : iter::range(m_N)) {
            ImGui::TableSetColumnIndex(j);
            auto const offset{i * m_N + j};

            // Get current character
            auto ch{m_board.at(offset)};

            // Replace null character with whitespace because the button label
            // cannot be an empty string
            if (ch == 0) {
              ch = ' ';
              ImGui::PushStyleColor(ImGuiCol_Button, gray_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonActive, gray_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonHovered, gray_color);
            } else if (ch == '1') {
              ImGui::PushStyleColor(ImGuiCol_Button, black_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonActive, black_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonHovered, black_color);
            } else if (ch == '2') {
              ImGui::PushStyleColor(ImGuiCol_Button, white_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonActive, white_color);
              ImGui::PushStyleColor(ImGuiCol_ButtonHovered, white_color);
            }

            // Button text is ch followed by an ID in the format ##ij
            auto buttonText{fmt::format("##{}{}", i, j)};
            if (ImGui::Button(buttonText.c_str(), ImVec2(-1, buttonHeight))) {
                m_board.at(offset) = m_XsTurn ? '1' : '2';
                m_XsTurn = !m_XsTurn;
            }
            ImGui::PopStyleColor(3);
          }
        }
        ImGui::EndTable();
      }
    }
    ImGui::End();
  }
}

void Window::newGame() {
  m_board.fill('\0');
}