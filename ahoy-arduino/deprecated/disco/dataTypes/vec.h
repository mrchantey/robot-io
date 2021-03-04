

template <typename T, int num>
class Vec
{
  public:
    int length = num;
    T val[num];
    Vec()
    {
    }
    void operator*=(T _val)
    {
        for (int i = 0; i < length; i++)
        {
            val[i] *= _val;
        }
    }

    template <typename outT>
    Vec<outT, num> Map(T minIn, T maxIn, outT minOut, outT maxOut)
    {
        Vec<outT, num> vec = Vec<outT, num>();
        for (int i = 0; i < num; i++)
        {
            vec.val[i] = Math::Map(val[i], minIn, maxIn, minOut, maxOut);
        }
        return vec;
    }

    virtual String ToString(char *prefix = "values: ", char *suffix = "\t")
    {
        String str = String(prefix);
        for (int i = 0; i < num; i++)
        {
            str += i;
            str += ": ";
            str += val[i];
            str += "\t";
        }
        str += suffix;
        return str;
    }

    virtual void Print(char *prefix = "values: ", char *suffix = "\t")
    {
        // String str = ToString(prefix, suffix);
        // Serial.print(str);
    }

    virtual String ToJson(char *prefix = "values: ")
    {
        return ToString();
    }
};

template <typename T, int num = 1>
class Vec1 : public Vec<T, num>
{
  public:
    Vec1(T _x = 0)
    {
        x(_x);
    }
    T x() { return this->val[0]; }
    void x(T _val) { this->val[0] = _val; }
};
template <typename T, int num = 2>
class Vec2 : public Vec1<T, num>
{
  public:
    Vec2(T _x = 0, T _y = 0) : Vec1<T, num>(_x)
    {
        y(_y);
    }
    T y() { return this->val[1]; }
    void y(T _val) { this->val[1] = _val; }
};
template <typename T, int num = 3>
class Vec3 : public Vec2<T, num>
{
  public:
    Vec3(T _x = 0, T _y = 0, T _z = 0) : Vec2<T, num>(_x, _y)
    {
        z(_z);
    }
    T z() { return this->val[2]; }
    void z(T _val) { this->val[2] = _val; }

    void Print(const char *prefix = "vec:\t", const char *suffix = "\t")
    {
        Serial.print(prefix);
        char str[128];
        sprintf(str, "x: %d\ty: %d\tz: %d", this->val[0], this->val[1], this->val[2]);
        Serial.print(str);
        Serial.print(suffix);
    }
};

class Vec3Float : public Vec3<float>
{
  public:
    Vec3Float(float _x = 0, float _y = 0, float _z = 0) : Vec3<float>(_x, _y, _z) {}
};

class Vec3Int : public Vec3<int>
{
  public:
    Vec3Int(int _x = 0, int _y = 0, int _z = 0) : Vec3<int>(_x, _y, _z) {}
};

// class VecFloat3 : public Vec3<float>
// {
//     //   public:
//     //     VecFloat3(float _x, float _y, float _z)
//     //     {
//     //         this->val[0] = _x;
//     //         this->val[1] = _y;
//     //         this->val[2] = _z;
//     //     }
// };