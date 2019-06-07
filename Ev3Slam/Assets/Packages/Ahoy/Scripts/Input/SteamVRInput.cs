// using UnityEngine;
// // using Valve.VR;
// // using Ahoy;


// using BoolAction = Valve.VR.SteamVR_Action_Boolean;
// using FloatAction = Valve.VR.SteamVR_Action_Single;
// using Vector2Action = Valve.VR.SteamVR_Action_Vector2;
// using NullEvent = Ahoy.NullUnityEvent;
// using BoolEvent = Ahoy.BoolUnityEvent;
// using FloatEvent = Ahoy.FloatUnityEvent;
// using Source = Valve.VR.SteamVR_Input_Sources;
// namespace Volumetric
// {

//     public class SteamVRInput : MonoBehaviour
//     {
//         [Range(0, 1)]
//         public float deadzone = 0.1f;

//         public BoolAction grabGrip;
//         public FloatAction squeeze;
//         public Vector2Action trackpadTouch;

//         public BoolEvent onSqueezeChangeLeft;
//         public BoolEvent onSqueezeChangeRight;

//         public FloatEvent onTrackpadTouchXLeft;
//         public FloatEvent onTrackpadTouchXRight;

//         // public NullEvent onGrabGripLeft;
//         // public NullEvent onGrabGripRight;
//         public NullEvent onGrabGripLeft;
//         public NullEvent onGrabGripRight;

//         public FloatEvent onSqueezeLeft;
//         public FloatEvent onSqueezeRight;

//         private void Update()
//         {

//             CheckVector2XAction(trackpadTouch, onTrackpadTouchXLeft, Source.LeftHand);
//             CheckVector2XAction(trackpadTouch, onTrackpadTouchXRight, Source.RightHand);
//             // CheckBoolAction(grabGrip, onGrabGripLeft, Source.LeftHand);
//             // CheckBoolAction(grabGrip, onGrabGripRight, Source.RightHand);
//             CheckBoolAction(grabGrip, onGrabGripLeft, Source.LeftHand);
//             CheckBoolAction(grabGrip, onGrabGripRight, Source.RightHand);
//             CheckSqueezeChange(squeeze, onSqueezeChangeLeft, Source.LeftHand);
//             CheckSqueezeChange(squeeze, onSqueezeChangeRight, Source.RightHand);
//             CheckFloatAction(squeeze, onSqueezeLeft, Source.LeftHand);
//             CheckFloatAction(squeeze, onSqueezeRight, Source.RightHand);
//         }


//         void CheckVector2XAction(Vector2Action action, FloatEvent onValue, Source source)
//         {
//             var val = action.GetAxis(source).x;
//             if (val > deadzone || val < -deadzone)
//                 onValue.Invoke(val);
//         }

//         void CheckFloatAction(FloatAction action, FloatEvent onValue, Source source)
//         {
//             float val = action.GetAxis(source);
//             if (val > deadzone || val < -deadzone)
//                 onValue.Invoke(val);
//         }

//         void CheckSqueezeChange(FloatAction action, BoolEvent onChange, Source source)
//         {
//             if (action.GetAxis(source) == 0 && action.GetLastAxis(source) != 0)
//                 onChange.Invoke(false);
//             if (action.GetAxis(source) != 0 && action.GetLastAxis(source) == 0)
//                 onChange.Invoke(true);
//         }


//         void CheckBoolAction(BoolAction action, NullEvent onChange, Source source)
//         {
//             // if (action.GetState(source))
//             //     onChange.Invoke();
//             if (action.GetStateDown(source))
//                 onChange.Invoke();
//             // if (action.GetStateUp(source))
//             //     onChange.Invoke(false);
//         }
//     }

// }