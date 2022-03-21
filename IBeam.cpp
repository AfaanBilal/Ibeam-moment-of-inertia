/*
 * IBeam - Moment of Inertia
 * (c) Afaan Bilal ( https://afaan.dev )
 *
 * A C++ class to calculate and print the moment of inertia 
 * of an I-beam about its centroid.
 *
*/

#include <iostream>

struct IBeamPart
{
    double width, height, ybar, h;
    double I;
};

class IBeam
{
    IBeamPart Flange_upper;
    IBeamPart Flange_lower;
    IBeamPart Web;

    double mYbar;
    double mI;

public:
    IBeam() {}
    IBeam(double ufw, double ufh, double ww, double wh, double lfw, double lfh)
    {
        Flange_upper.width = ufw;
        Flange_upper.height = ufh;
        Web.width = ww;
        Web.height = wh;
        Flange_lower.width = lfw;
        Flange_lower.height = lfh;
    }

    void inputDimensions()
    {
        std::cout << "Enter the width of upper flange: ";
        std::cin >> Flange_upper.width;
        std::cout << "Enter the height of upper flange: ";
        std::cin >> Flange_upper.height;
        std::cout << "Enter the width of web: ";
        std::cin >> Web.width;
        std::cout << "Enter the height of web: ";
        std::cin >> Web.height;
        std::cout << "Enter the width of lower flange: ";
        std::cin >> Flange_lower.width;
        std::cout << "Enter the height of lower flange: ";
        std::cin >> Flange_lower.height;
    }

    double areaOf(IBeamPart ibp)
    {
        return ibp.width * ibp.height;
    }

    double MOIof(IBeamPart ibp)
    {
        return ( ibp.width * ibp.height * ibp.height * ibp.height ) / 12;
    }

    double MOIaboutHof(IBeamPart ibp)
    {  
        return ibp.I + areaOf(ibp) * ibp.h * ibp.h;
    }

    double Hof(IBeamPart ibp)
    {
        return (mYbar > ibp.ybar) ? mYbar - ibp.ybar : ibp.ybar - mYbar;
    }

    void calculateMOI()
    {
        Flange_lower.ybar = Flange_lower.height / 2;
        Web.ybar = Flange_lower.height + Web.height / 2;
        Flange_upper.ybar = Flange_lower.height + Web.height + Flange_upper.height / 2;

        mYbar = (  areaOf(Flange_lower) * Flange_lower.ybar 
                + areaOf(Web) * Web.ybar 
                + areaOf(Flange_upper) * Flange_upper.ybar ) 
                / ( areaOf(Flange_lower) + areaOf(Web) + areaOf(Flange_upper) );

        Flange_lower.I = MOIof(Flange_lower);
        Web.I = MOIof(Web);
        Flange_upper.I = MOIof(Flange_upper);

        Flange_lower.h = Hof(Flange_lower);
        Web.h = Hof(Web);
        Flange_upper.h = Hof(Flange_upper);

        mI = MOIaboutHof(Flange_lower) + MOIaboutHof(Web) + MOIaboutHof(Flange_upper);
    }

    void printMOI()
    {
        calculateMOI();
        std::cout << "MOI: " << mI;
    }

};

int main()
{
    IBeam iBeam;

    std::cout << "IBeam Moment of Inertia\n(c) Afaan Bilal (https://afaan.ml)\n";
    iBeam.inputDimensions();
    iBeam.printMOI();
}
