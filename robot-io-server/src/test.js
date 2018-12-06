import RobotIO from './index';

const robotIO = RobotIO()

testSendData()

function testSendData() {
    const startMillis = Date.now()
    setInterval(() => {
        robotIO.server.sendData({
            mpu: {
                acc: {
                    x: Math.random(),
                    y: Math.random(),
                    z: Math.random()
                },
                gyro: {
                    x: Math.random(),
                    y: Math.random(),
                    z: Math.random()
                }
            },
            timeStamp: Date.now() - startMillis
        })
    }, 100);


}
