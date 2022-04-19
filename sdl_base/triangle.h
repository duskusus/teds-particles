class Triangle {
    public:
    vec2 a;
    vec2 b;
    vec2 c;
    Color fill;
    Triangle(const vec2 &_a,const vec2 &_b, const vec2 &_c, const Color &_fill) {
        a = _a;
        b = _b;
        c = _c;
        fill = _fill;
    };
};