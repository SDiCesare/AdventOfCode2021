class Lanternfish
{
public:
    Lanternfish(int _age)
    {
        age = _age;
    }

    void tick()
    {
        age--;
    }

    Lanternfish *makeChild()
    {
        age = 7;
        return new Lanternfish(8);
    }

    int getAge()
    {
        return age;
    }

private:
    int age;
};