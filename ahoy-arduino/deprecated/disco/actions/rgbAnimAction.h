
// #include "disco.h"

// class RGBAnimAction : public AnimAction<Color>
// {
//   public:
//     Color startColor;
//     Color endColor;

//     RGBAnimAction(Color _startColor = Color(0, 0, 0), Color _endColor = Color(1, 1, 1))
//     {
//         startColor = _startColor;
//         endColor = _endColor;
//     }

//     void Animate(float t)
//     {
//         Color col = Color::Lerp(startColor, endColor, t);
//         action->Invoke(col);
//     }
// };