from .MotorSystem import MotorSystem
from .SensorSystem import SensorSystem
from .FakeMotorSystem import FakeMotorSystem
from .FakeSensorSystem import FakeSensorSystem
import ev3dev2

isDeployed = None


def GetIsDeployed():
    return isDeployed


motorSystem = None
sensorSystem = None
if(ev3dev2.get_current_platform() == 'fake'):
    motorSystem = FakeMotorSystem()
    sensorSystem = FakeSensorSystem()
    isDeployed = False
else:
    motorSystem = MotorSystem()
    sensorSystem = SensorSystem()
    isDeployed = True
