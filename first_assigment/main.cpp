// game_course.cpp : Defines the entry point for the application.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>
#include <vector>

#include "Config.h"


firstassigment::Config getConfig()
{
   try
   {
      firstassigment::Config config("config.json");
      return config;
   }
   catch (const std::exception& e)
   {
      std::cout << e.what();
      std::exit(0);
   }
}

struct ShapePlusInfo
{
   firstassigment::Config::ShapeInfo Info;
   std::unique_ptr< sf::Shape > Shape = nullptr;

   ShapePlusInfo(const firstassigment::Config::ShapeInfo& info,
      std::unique_ptr< sf::Shape >&& shape) :
      Info(info),
      Shape(std::move(shape))
   {}
};

std::vector< ShapePlusInfo  > makeShapes(const std::vector<firstassigment::Config::ShapeInfo>& initial_shapes)
{
   const auto makeCircle = [](const firstassigment::Config::ShapeInfo& shape_info)
   {
      ShapePlusInfo shape_plus_info(shape_info, std::move(std::make_unique< sf::CircleShape >(shape_info.Radius)));
      
      return shape_plus_info;
   };


   const auto makeRectangle = [](const firstassigment::Config::ShapeInfo& shape_info)
   {
      ShapePlusInfo shape_plus_info(shape_info, std::move(std::make_unique< sf::RectangleShape >(sf::Vector2f(shape_info.ShapeSize.Width, shape_info.ShapeSize.Height))));

      return shape_plus_info;
   };

   std::vector< ShapePlusInfo  >  shapes_plus_infos;

   for (const auto& shape_info : initial_shapes)
   {
      switch (shape_info.Type)
      {
      case firstassigment::Config::ShapeType::Circle:
      {
         shapes_plus_infos.push_back(makeCircle(shape_info));
      }
      continue;

      case firstassigment::Config::ShapeType::Retangle:
      {
         shapes_plus_infos.push_back(makeRectangle(shape_info));
      }
      continue;
      }
   }

   return shapes_plus_infos;
}

int main()
{
   const auto config = getConfig();

   sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(config.GetWindowSize().Width),
      static_cast<unsigned int>(config.GetWindowSize().Height)), "SFML first example");

   auto shapes_plus_infos = makeShapes(config.GetShapeInfos());


   // run the program as long as the window is open
   while (window.isOpen())
   {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
         // "close requested" event: we close the window
         if (event.type == sf::Event::Closed)
            window.close();
      }

      window.clear();

      for (const auto& shape_info : shapes_plus_infos)
      {
         shape_info.Shape->setPosition(shape_info.Info.Origin.X, shape_info.Info.Origin.Y);

         window.draw(*shape_info.Shape);
      }

      window.display();
   }

   return 0;
}
