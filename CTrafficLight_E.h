enum CTrafficLight_E
{
   Green,
   Yellow,
   Red,
   NumOfTrafficLightOptions
};

#ifdef __cplusplus
extern "C" {
#endif

const char * CTrafficLight_E_ToString(enum CTrafficLight_E light);

#ifdef __cplusplus
}
#endif
