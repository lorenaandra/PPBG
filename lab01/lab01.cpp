#include "lab/lab01/lab01.h"

#include <vector>

using namespace std;
using namespace lab;

Lab01::Lab01()
{
    window->SetSize(1280, 720);
}


Lab01::~Lab01()
{
}

void Lab01::Initialize()
{
    Exercise1();
    Exercise2();
    Exercise3();
    Exercise4();
    Exercise5();
    Exercise6();
}

void Lab01::Exercise1()
{
    SetExercise();

    //TODO(student): Ex. 1
    {
        SetPanel("1", { -3, -2, 100 }, { 0, 0, 1280, 720 });

        glm::vec2 v1(5, 2);
        glm::vec2 v2(2, 3);

        glm::vec2 result_vector = v1 + v2;

        RenderVector(v1, glm::vec3(1, 0, 0), "v1");
        RenderVector(v2, glm::vec3(0, 1, 0), "v2");
        RenderVector(result_vector, glm::vec3(0, 0, 1), "v12");


        glm::vec2 origin_for_v2(5, 2); 
        glm::vec2 origin_for_v1(2, 3);

        RenderVector(v1, glm::vec3(1, 0, 0), "v1", origin_for_v1);
        RenderVector(v2, glm::vec3(0, 1, 0), "v2", origin_for_v2);

    }
}

void Lab01::Exercise2()
{
    SetExercise();

    //TODO(student): Ex. 2
    {
        SetPanel("2", { -7, -5, 75 }, { 0, 0, 1280, 720 });

        {
            glm::vec2 p1(1, 1);
            glm::vec2 p2(3, -3);

            RenderPoint(p1, glm::vec3(1, 0, 0), "P1");
            RenderPoint(p2, glm::vec3(0, 0, 1), "P2");
            RenderVector(p1 - p2, glm::vec3(1, 0, 0.92), "v21", p2);

        }

        {
            glm::vec2 p3(-1, -2);
            glm::vec2 p4(-5, -4);

            RenderPoint(p3, glm::vec3(1, 0, 0), "P3");
            RenderPoint(p4, glm::vec3(0, 0, 1), "P4");
            RenderVector(p3 - p4, glm::vec3(1, 0, 0.92), "v43", p4);
        }

        {
            glm::vec2 p5(6, 3);
            glm::vec2 p6(4, 1);

            RenderPoint(p5, glm::vec3(1, 0, 0), "P5");
            RenderPoint(p6, glm::vec3(0, 0, 1), "P6");
            RenderVector(p6 - p5, glm::vec3(1, 0, 0.92), "v56", p5);
        }

        {
            glm::vec2 p7(5, 4);
            glm::vec2 p8(-3, 4);

            RenderPoint(p7, glm::vec3(1, 0, 0), "P7");
            RenderPoint(p8, glm::vec3(0, 0, 1), "P8");
            RenderVector(p7 - p8, glm::vec3(1, 0, 0.92), "v87", p8);
        }
    }
}

void Lab01::Exercise3()
{
    SetExercise();

    //TODO(student): Ex. 3
    {
        SetPanel("3", { -7, -5, 75 }, { 0, 0, 1280, 720 });

        glm::vec2 v1(4, 3);
        glm::vec2 v2(-3, 3);
        glm::vec2 v3(-6, -2);
        glm::vec2 v4(-2, -4);
        glm::vec2 v5(3, -2);

        RenderVector(v1, glm::vec3(1, 0, 0), "v1");
        RenderVector(v2, glm::vec3(0, 1, 0), "v2");
        RenderVector(v3, glm::vec3(0, 1, 1), "v3");
        RenderVector(v4, glm::vec3(0, 0, 1), "v4");
        RenderVector(v5, glm::vec3(1, 0, 1), "v5");


        RenderVector(glm::normalize(v1), glm::vec3(0, 0, 0));
        RenderVector(glm::normalize(v2), glm::vec3(0, 0, 0)); 
        RenderVector(glm::normalize(v3), glm::vec3(0, 0, 0)); 
        RenderVector(glm::normalize(v4), glm::vec3(0, 0, 0)); 
        RenderVector(glm::normalize(v5), glm::vec3(0, 0, 0)); 

    }
}

void Lab01::Exercise4()
{
    SetExercise ();

    //TODO(student): Ex. 4
    {
        SetPanel("4", { -3, -2, 100 }, { 0, 0, 1280, 720 });

        glm::vec2 v1(4, 1.5);
        glm::vec2 v2(2, 3);

        RenderVector(v1, glm::vec3(1, 0, 0), "v1");
        RenderVector(v2, glm::vec3(0, 1, 0), "v2");

        // find angle between v1 and v2
        float dot_product = glm::dot(glm::normalize(v1), glm::normalize(v2));
        float angle_between = acos(dot_product);  

        float start_angle_v1 = atan2(v1.y, v1.x);

        RenderArc(start_angle_v1, angle_between, glm::vec3(0, 0, 1), 3.0f);


        /// bonus
        float start_angle_bonus = atan2(v2.y, v2.x);
        RenderArc(start_angle_bonus, 2.0f * glm::pi<float>() - angle_between, glm::vec3(1, 0, 0), 1.0f);


        //void RenderArc(float start_angle, float angle, const glm::vec3 & color,
        //    float radius = 3.0f, const glm::vec2 & center = glm::vec2(0.0f));
    }
}

void Lab01::Exercise5()
{
    SetExercise();

    //TODO(student): Ex. 5
    {
        SetPanel("5", { -7, -5, 75 }, { 0, 0, 1280, 720 });

        auto compute_area_with_heron = [](const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) -> float {

            float a = glm::length(p2 - p1);  
            float b = glm::length(p3 - p1);
            float c = glm::length(p3 - p2);
            float s = (a + b + c) / 2.0f; 

            return sqrt(s * (s - a) * (s - b) * (s - c));
            };

        {
            glm::vec2 p1(1, 1);
            glm::vec2 p2(3, 1);
            glm::vec2 p3(2, 4);

            RenderTriangle(p1, p2, p3, glm::vec3(0, 1, 1));

            RenderPoint(p1, glm::vec3(1, 0, 0), "P1");
            RenderPoint(p2, glm::vec3(0, 0, 1), "P2");
            RenderPoint(p3, glm::vec3(0, 1, 0), "P3");

            float area_first_triangle = compute_area_with_heron(p1, p2, p3);
            RenderText(glm::vec2(2, 2), std::to_string(area_first_triangle), glm::vec3(0, 0, 0));
        }

        {
            glm::vec2 p1(-1.5, -3.7);
            glm::vec2 p2(-2.5, 3.2);
            glm::vec2 p3(-6.1, 2.9);

            RenderTriangle(p1, p2, p3, glm::vec3(0, 1, 1));

            RenderPoint(p1, glm::vec3(1, 0, 0), "P1");
            RenderPoint(p2, glm::vec3(0, 0, 1), "P2");
            RenderPoint(p3, glm::vec3(0, 1, 0), "P3");

            float area_second_triangle = compute_area_with_heron(p1, p2, p3);
            RenderText(glm::vec2(-3, 1), std::to_string(area_second_triangle), glm::vec3(0, 0, 0));

        }

        {
            glm::vec2 p1(2.3, -2.1);
            glm::vec2 p2(7.1, -3.5);
            glm::vec2 p3(7.5, 3.7);

            RenderTriangle(p1, p2, p3, glm::vec3(0, 1, 1));

            RenderPoint(p1, glm::vec3(1, 0, 0), "P1");
            RenderPoint(p2, glm::vec3(0, 0, 1), "P2");
            RenderPoint(p3, glm::vec3(0, 1, 0), "P3");

            float area_third_triangle = compute_area_with_heron(p1, p2, p3);
            RenderText(glm::vec2(6, -1), std::to_string(area_third_triangle), glm::vec3(0, 0, 0));

        }
    }
}

void Lab01::Exercise6()
{
    SetExercise();

    //TODO(student): Ex. 6
    {
        SetPanel("6", { -7, -5, 75 }, { 0, 0, 1280, 720 });

        glm::vec2 p1(-4, 3);
        glm::vec2 p2(6, 2);
        glm::vec2 p3(1, -4);

        RenderTriangle(p1, p2, p3, glm::vec3(0, 1, 1));

        RenderPoint(p1, glm::vec3(0, 0, 1), "P1");
        RenderPoint(p2, glm::vec3(0, 0, 1), "P2");
        RenderPoint(p3, glm::vec3(0, 0, 1), "P3");

        ///// these are points to check
        std::vector<glm::vec2> check_points{
            glm::vec2(1, 1), glm::vec2(3.21, 3.2),
            glm::vec2(-2.16, 2.9), glm::vec2(2, -2),
            glm::vec2(-1.1, -0.9), glm::vec2(-1.9, 2.1),
            glm::vec2(-4, 0), glm::vec2(-4, -2.5),
            glm::vec2(4.5, 1.1), glm::vec2(5.9, -3.1),
            glm::vec2(7.1, 1.9), glm::vec2(-5.9, 1.5)
        };

        /*for (const glm::vec2 &check_point : check_points) {
            RenderPoint(check_point, glm::vec3(0), "?");
        }*/

        const float EPSILON = 0.01f;

        auto CalculateArea = [](const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& v3) -> float {
            return glm::abs((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0f);
            };


        float large_triangle_area = CalculateArea(p1, p2, p3);

        for (const glm::vec2& check_point : check_points) {

            float area1 = CalculateArea(check_point, p2, p3);
            float area2 = CalculateArea(p1, check_point, p3);
            float area3 = CalculateArea(p1, p2, check_point);

            float resulted_sum_area = area1 + area2 + area3;

            bool inside_triangle = abs(large_triangle_area - resulted_sum_area) < EPSILON;


            if (inside_triangle) {
                RenderPoint(check_point, glm::vec3(0, 1, 0), "in");
            }
            else {
                RenderPoint(check_point, glm::vec3(1, 0, 0), "out");
            }


        }
    }
}
