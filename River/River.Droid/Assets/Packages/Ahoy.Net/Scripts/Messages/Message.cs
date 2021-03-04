


namespace Ahoy.Net
{

    public class Message
    {
        public byte channel;
        public byte command;
        public DataType dataType;

        public Message(byte _channel, byte _command, DataType _dataType)
        {
            channel = _channel;
            command = _command;
            dataType = _dataType;
        }

        public override string ToString()
        {
            return $"channel: {channel}, command: {command}, data type: {dataType}";
        }
    }

    public class Message<T> : Message
    {
        public T[] data;
        public Message(byte _channel, byte _command, DataType _dataType, T[] _data)
        : base(_channel, _command, _dataType)
        {
            data = _data;
        }


        public override string ToString()
        {
            return base.ToString() + $", data length: {data.Length}, data: {data.ElementsToString()}";
        }
    }


}