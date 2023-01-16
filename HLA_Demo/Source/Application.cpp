#include "Gui/GuiApp.h"
#include "imgui.h"

#include "Matrix.h"
#include "Common.h"


static ImVec2 g_WindowDimensions = { 800, 800 };
static bool showAbout = false;

namespace GUIComponents
{
	static void About()
	{
		ImGui::Begin("About", &showAbout);
		ImGui::TextWrapped("Pre-Release HLA GUI Demo");
		ImGui::End();
	}
}

void GUIMain()
{
	auto& guiInstance = WrapGui::GuiApp::Get();
	ImGui::SetNextWindowSize(g_WindowDimensions);
	ImGui::Begin("HLA Library GUI Demo", guiInstance.GetRunStatePtr(), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("About"))
			{
				showAbout = true;
			}
			if (ImGui::MenuItem("Exit"))
			{
				guiInstance.Close();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	HLA::Matrix m0({ 1, 2, 3, 4 }, { 2,2 });
	HLA::Matrix m1({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 3,3 });
	HLA::Matrix m2({ 1, 2, 3, 4, 5, 6 }, { 3,2 });
	HLA::Matrix m3 = HLA::Zero(3, 3);
	m3(0, 0) = 1;
	m3(1, 1) = 2;
	m3(2, 2) = 1;

	HLA::Matrix vec0{ { -3, 2, 1, }, { 3, 1 } };
	HLA::Matrix vec1{ { -3, 3, 5, }, { 3, 1 } };


	if (ImGui::CollapsingHeader("Matrix Creation"))
	{
		ImGui::Text("m0 = \n%s\nm1 = \n%s\nm2 = \n%s\nm3 = \n%s\nvec0 = \n%s\nvec1 = \n%s\n",
			m0.PrintFormat().c_str(), m1.PrintFormat().c_str(), m2.PrintFormat().c_str(), m3.PrintFormat().c_str(), vec0.PrintFormat().c_str(), vec1.PrintFormat().c_str());
	}

	if (ImGui::CollapsingHeader("Matrix Functions"))
	{
		
		ImGui::Text("Is Matrix a Vector?\n%d\n", m1.IsVector());
		ImGui::Text("Is Matrix a Square?\n%d\n", HLA::IsSquare(m1));
		ImGui::Text("m0 Determinant:\n%.0000f\n", m0.Determinant());
		ImGui::Text("m0 Inverse:\n%s\n", m0.Inverse().PrintFormat().c_str());
		ImGui::Text("m3 Inverse:\n%s\n", m3.Inverse().PrintFormat().c_str());
		ImGui::Text("m1 l1 norm:\n%.0000f\n", m1.Norm(1));
		ImGui::Text("m1 l2 norm:\n%s\n", std::to_string(m1.Norm(2)).c_str());
		ImGui::Text("m1 Shape:\n(%llu, %llu)\n", m1.Shape().r, m1.Shape().c);
		ImGui::Text("m1 Trace:\n%.0000f\n", m1.Trace());
		ImGui::Text("m1 Transpose:\n%s\n", m1.Transpose().PrintFormat().c_str());
		ImGui::Text("Dot Product of vec0 & vec1:\n%.0000f\n", HLA::Dot(std::vector<double>(vec0), std::vector<double>(vec1)));
		const double angle = HLA::TwoVectorAngle(std::vector<double>(vec0), std::vector<double>(vec1));
		ImGui::Text("Angle of vec0 & vec1 in RAD:\n%s\n", std::to_string(angle).c_str());
	}

	if (ImGui::CollapsingHeader("Matrix Arithmetic"))
	{
		ImGui::Text("vec0 * transpose(vec1):\n%s\n", (vec0 * vec1.Transpose()).PrintFormat().c_str());
		ImGui::Text("transpose(vec0) * vec1:\n%s\n", (vec0.Transpose() * vec1).PrintFormat().c_str());
		ImGui::Text("vec1 + vec 2:\n%s\n", (vec0 + vec1).PrintFormat().c_str());
		ImGui::Text("m2 + m2:\n%s\n", (m2 + m2).PrintFormat().c_str());
		ImGui::Text("m1 - m1:\n%s\n", (m1 - m1).PrintFormat().c_str());
		ImGui::Text("m1 * m1:\n%s\n", (m1 * m1).PrintFormat().c_str());
	}

	if (ImGui::CollapsingHeader("Extra Test Cases"))
	{
		if (ImGui::CollapsingHeader("Matrix Generation"))
		{

			HLA::Matrix a = { {5, 1, 2, 1, 3, 7, 2, 7, 8}, {3, 3} };
			HLA::Matrix b = { {1, 2, -4, 5}, {4, 1} };
			HLA::Matrix c = HLA::Zero(3, 2);
			HLA::Matrix d = { {2, 1, 3, 6, 7},{1, 5} };
			ImGui::Text("a:\n%s\n", a.PrintFormat().c_str());
			ImGui::Text("b:\n%s\n", b.PrintFormat().c_str());
			ImGui::Text("c:\n%s\n", c.PrintFormat().c_str());
			ImGui::Text("d:\n%s\n", d.PrintFormat().c_str());
		}
		if (ImGui::CollapsingHeader("Marix Arithmetic"))
		{
			if (ImGui::CollapsingHeader("1"))
			{
				auto a = HLA::Matrix{ {2, 1, 3, 3, -2, 1, 1, 0, 1}, {3,3} };
				auto b = HLA::Matrix{ {1, -2, 2, 1, 4, 2}, {3, 2} };
				ImGui::Text("A = \n%s\n", a.PrintFormat().c_str());
				ImGui::Text("B = \n%s\n", b.PrintFormat().c_str());
				try
				{
					ImGui::Text("A + B=\n%s\n", (a + b).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
			if (ImGui::CollapsingHeader("2"))
			{
				auto a = HLA::Matrix{ {2,1,3}, {1,3} };
				auto b = HLA::Matrix{ {2,1,3}, {3,1} };
				ImGui::Text("A = \n%s\n", a.PrintFormat().c_str());
				ImGui::Text("B = \n%s\n", b.PrintFormat().c_str());
				try
				{
					ImGui::Text("A * B=\n%s\n", (a * b).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
			if (ImGui::CollapsingHeader("3"))
			{
				auto f = HLA::Matrix{ {2,-1,3, 0, -5, 2}, {3,2} };
				auto h = HLA::Matrix{ {1,6,-1, -2, 0, 3}, {3,2} };
				ImGui::Text("F = \n%s\n", f.PrintFormat().c_str());
				ImGui::Text("H = \n%s\n", h.PrintFormat().c_str());
				try
				{
					ImGui::Text("F + H=\n%s\n", (f + h).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
			if (ImGui::CollapsingHeader("4"))
			{
				auto c = HLA::Matrix{ {3, -1, -2, 2}, {2,2} };
				auto a = HLA::Matrix{ {2, 0, 1, 4}, {2,2} };
				ImGui::Text("C = \n%s\n", c.PrintFormat().c_str());
				ImGui::Text("A = \n%s\n", a.PrintFormat().c_str());
				try
				{
					ImGui::Text("C - A=\n%s\n", (c - a).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
			if (ImGui::CollapsingHeader("5"))
			{
				auto a = HLA::Matrix{ {1,0,-3, -2, 4, 1}, {2, 3} };
				auto b = HLA::Matrix{ {1, 0, 4, 1, -2, 3, -1, 5, 0, -1, 2, 1}, {3, 4} };
				ImGui::Text("A = \n%s\n", a.PrintFormat().c_str());
				ImGui::Text("B = \n%s\n", b.PrintFormat().c_str());
				try
				{
					ImGui::Text("A * B=\n%s\n", (a * b).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
			if (ImGui::CollapsingHeader("6"))
			{
				auto c = HLA::Matrix{ {1, -2, 0, 4, -3, 1}, {3,2} };
				auto d = HLA::Matrix{ {2, -1, 3, 0}, {2,2} };
				ImGui::Text("C = \n%s\n", c.PrintFormat().c_str());
				ImGui::Text("D = \n%s\n", d.PrintFormat().c_str());
				try
				{
					ImGui::Text("D * C=\n%s\n", (d * c).PrintFormat().c_str());
				}
				catch (std::exception& e)
				{
					ImGui::Text("%s", e.what());
				}
			}
		}
	}

	if (showAbout)
	{
		GUIComponents::About();
	}

	ImGui::End();
}

int main()
{
	WrapGui::GuiApp::InitGui({ "", 1, 1 });
	auto& guiInstance = WrapGui::GuiApp::Get();
	guiInstance.HideWindow();
	guiInstance.SetMain(GUIMain);
	guiInstance.Run();
}
