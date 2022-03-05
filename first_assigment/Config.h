#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

namespace firstassigment
{
   class Config
   {
   public:
      struct Size
      {
         float Width = 0.0;
         float Height = 0.0;
      };

      struct PointValue
      {
         uint32_t X = 0;
         uint32_t Y = 0;
      };

      struct SpeedValue
      {
         float X = 0.0;
         float Y = 0.0;
      };


      struct ColorValue
      {
         uint8_t R = 0;
         uint8_t G = 0;
         uint8_t B = 0;
      };

      enum class ShapeType
      {
         None = 0,
         Circle,
         Retangle
      };

      struct ShapeInfo
      {
         std::string Label;
         PointValue Origin;
         SpeedValue Speed;
         ColorValue Color;
         Size ShapeSize;
         float Radius = 0.0;
         ShapeType Type = ShapeType::None;
      };

      Config(const std::string& filepath);
      const Size& GetWindowSize()const;
      const std::vector<ShapeInfo>& GetShapeInfos() const;

   private:
      Size m_window_size;
      std::vector< ShapeInfo > m_shapes;

      static  ShapeInfo make(const nlohmann::json& json);
   };
}