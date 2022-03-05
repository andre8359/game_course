#include "Config.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace firstassigment
{
   Config::Config(const std::string& filepath)
   {
      std::ifstream config_file;
      config_file.open(filepath);

      if (!config_file.good())
      {
         throw std::runtime_error("Config file not found.");
      }

      nlohmann::json config_json;
      config_file >> config_json;

      m_window_size.Width = config_json.at("Window").at("Width").get<float>();
      m_window_size.Height = config_json.at("Window").at("Height").get<float>();

      for (const auto& shape : config_json.at("Shapes"))
      {
         m_shapes.push_back(make(shape));
      }
   }

   const Config::Size& Config::GetWindowSize() const
   {
      return m_window_size;
   }

   const std::vector<Config::ShapeInfo>& Config::GetShapeInfos() const
   {
      return m_shapes;
   }

   Config::ShapeInfo Config::make(const nlohmann::json& json)
   {
      ShapeInfo shape;
      shape.Type = static_cast<Config::ShapeType>(json.at("Type").get<int32_t>());
      shape.Label = json.at("Label").get<std::string>();
      shape.Origin.X = json.at("Origin").at("x").get<uint32_t>();
      shape.Origin.Y = json.at("Origin").at("y").get<uint32_t>();
      shape.Speed.X = json.at("Speed").at("x").get<float>();
      shape.Speed.Y = json.at("Speed").at("y").get<float>();
      shape.Color.R = json.at("Color")[0].get<uint8_t>();
      shape.Color.G = json.at("Color")[1].get<uint8_t>();
      shape.Color.B = json.at("Color")[2].get<uint8_t>();

      if (shape.Type == ShapeType::Circle)
      {
         shape.Radius = json.at("Radius").get<float>();
         return shape;
      }

      shape.ShapeSize.Width = json.at("Size").at("Width").get<float>();
      shape.ShapeSize.Width = json.at("Size").at("Height").get<float>();

      return shape;
   }
}