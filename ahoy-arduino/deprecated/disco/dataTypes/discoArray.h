

template <typename dataT>
class DiscoArray
{
  public:
    dataT *arr;
    uint len;

    DiscoArray(dataT *_arr, uint _len)
    {
        arr = _arr;
        len = _len;
    }

    String ToString()
    {
        String str = String("");
        for (int i = 0; i < len; i++)
        {
            str += arr[i];
        }
        return str;
    }

    String ToBits()
    {
        return Data::ConvertToBits(arr, len);
    }
};
