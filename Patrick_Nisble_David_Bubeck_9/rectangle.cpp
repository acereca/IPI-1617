#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

/////////////////////////////////////////////////
// die 2-dimensionale Punkt-Klasse aus der Vorlesung
class Point
{
    // die Koordinaten des Punktes
    double x_;
    double y_;

  public:

    // Standardkonstruktor: initialisiere Punkt (0,0)
    Point()
    : x_(0.0)
    , y_(0.0)
    {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
    Point(double x, double y)
    : x_(x)
    , y_(y)
    {}

    // Getter-Funktionen fuer die Koordinaten
    double x() const
    {
        return (*this).x_;
    }

    double y() const
    {
        return (*this).y_;
    }

    // teste ob zwei Punkte gleich sind
    bool operator==(Point const & other) const
    {
        return (*this).x() == other.x() && (*this).y() == other.y();
    }

    // teste ob zwei Punkte ungleich sind
    bool operator!=(Point const & other) const
    {
        return (*this).x() != other.x() || (*this).y() != other.y();
    }

    // erzeuge neuen Punkt, desssen x- und y-Koordinate
    // vertauscht sind
    Point transpose() const
    {
        Point res((*this).y(), (*this).x());
        return res;
    }

    // erzeuge neuen Punkt, der um den Vektor v verschoben ist
    Point translate(Point const & v) const
    {
        Point res((*this).x() + v.x(), (*this).y() + v.y());
        return res;
    }
};

// wandle den Punkt in einen String der Form "[x, y]"
std::string to_string(Point const & p)
{
    return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

/////////////////////////////////////////////////
// Implementieren Sie die Rectangle-Klasse.
class Rectangle
{
    Point p0_; // linke untere Ecke
    Point p1_; // rechte obere Ecke

  public:

    // Implementieren Sie die folgenden Konstruktoren.
    Rectangle() : p0_(Point(0,0)), p1_(Point(0,0))
    {}

    Rectangle(Point const & p1) : p0_(Point(0,0)), p1_(p1)
    {}

    Rectangle(Point const & p0, Point const & p1) : p0_(p0), p1_(p1)
    {}

    // read-only Getter-Funktionen fuer die Member-Variablen
    Point const & p0() const
    {
        return (*this).p0_;
    }

    Point const & p1() const
    {
        return (*this).p1_;
    }

    // Implementieren Sie die folgenden Getter-Funktionen.
    double x0() const // linke x-Koordinate
    {
        return p0_.x();
    }

    double x1() const // rechte x-Koordinate
    {
        return p1_.x();
    }

    double y0() const // untere y-Koordinate
    {
        return p0_.y();
    }

    double y1() const // obere  y-Koordinate
    {
        return p1_.y();
    }

    double width() const  // Breite
    {
        return x1()-x0();
    }

    double height() const // Hoehe
    {
        return y1()-y0();
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn das Rechteck nicht ungueltig ist.
    bool is_valid() const
    {
        return (p0_.x() < p1_.x() && p0_.y() < p1_.y());
    }

    // Implementieren Sie eine Funktion, die die Flaeche des
    // Rechtecks zurueckgibt, bzw. -1.0, wenn das Rechteck
    // ungueltig ist.
    double area() const
    {
        if (is_valid()) {
            return height()*width();
        }
        return -1.0;
    }

    // Implementieren Sie eine Funktion, die ein neues Rechteck
    // zurueckgibt, bei dem die x- und y-Koordinaten vertauscht sind.
    Rectangle transpose() const
    {
        return Rectangle(p0_.transpose(),p1_.transpose());
    }

    // Implementieren Sie eine Funktion, die ein neues Rechteck
    // zurueckgibt, das um den Vektor v verschoben ist.
    Rectangle translate(Point const & v) const
    {
        return Rectangle(p0_.translate(v), p1_.translate(v));
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn der Punkt p im Rechteck (*this) enthalten
    // ist. Wenn (*this) ungueltig ist, soll 'false' zurueckgegeben
    // werden.
    bool contains(Point const & p) const
    {
        if (is_valid()){
            return (p.x()-p0_.x()) <= width() && (p.y()-p0_.y()) <= height();
        }
        return false;
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn das Rechteck r im Rechteck (*this) enthalten
    // ist. Wenn (*this) oder r ungueltig sind, soll 'false' zurueckgegeben
    // werden.
    bool contains(Rectangle const & r) const
    {
        if (is_valid() || r.is_valid()) {
            return (contains(r.p0()) && contains(r.p1()));
        }
        return false;
    }

    /// operator overload for rectangle comparison
    /// \param r
    /// \return
    bool operator==(Rectangle const & r) const {
        if (this->p0_ == r.p0() && this->p1_ == r.p1()){
            return true;
        }
        return false;
    }
};

// Implementieren Sie eine Funktion, die das Rechteck
// in einen String der Form "[x0:x1, y0:y1]" umwandelt.
std::string to_string(Rectangle const & r)
{
    return "[" + std::to_string(r.x0())
           + ":" + std::to_string(r.x1())
            + ", " + std::to_string(r.y0())
            + ":" + std::to_string(r.y1())
            + "]";
}

// Implementieren Sie eine Funktion, die das kleinste Rechteck
// zurueckgibt, das r1 und r2 enthaelt.
Rectangle rectangle_union(Rectangle const & r1, Rectangle const & r2)
{
    if (r1.is_valid() && r2.is_valid()){
        Point rp0 = Point(std::min(r1.x0(), r2.x0()), std::min(r1.y0(), r2.y0()));
        Point rp1 = Point(std::max(r1.x1(), r2.x1()), std::max(r1.y1(), r2.y1()));
        return Rectangle(rp0, rp1);
    }
    return Rectangle();
}

// Implementieren Sie eine Funktion, die den Durchschnitt
// der Rechtecke r1 und r2 zerueckgibt, oder ein beliebiges
// ungueltiges Rechteck, falls r1 und r2 nicht ueberlappen.
Rectangle rectangle_intersection(Rectangle const & r1, Rectangle const & r2)
{
    if (r1.is_valid() && r2.is_valid()) {
        if (r1.contains(r2.p0()) || r1.contains(r2.p1()) || r1.contains(Point(r1.x0(), r1.y1())) || r1.contains(Point(r1.x1(), r1.y0()))){
            Point rp0 = Point(std::max(r1.x0(), r2.x0()), std::max(r1.y0(), r2.y0()));
            Point rp1 = Point(std::min(r1.x1(), r2.x1()), std::min(r1.y1(), r2.y1()));
            return Rectangle(rp0, rp1);
        }
    }
    return Rectangle();
}

// Implementieren Sie Tests fuer die Rectangle-Klasse.
void testRectangle()
{
    Rectangle r0(Point(3.0, 5.0));

    assert(r0.p0() == Point(0.0, 0.0));
    assert(r0.p1() == Point(3.0, 5.0));

    Rectangle r(Point(1.0, 2.0), Point(3.0, 5.0));

    assert(r.x0() == 1.0);

    // Fuegen Sie weitere Tests entsprechend der Aufgabe hinzu.

    // b
    Rectangle t1;
    assert(0.0 == t1.x0());
    assert(0.0 == t1.y0());
    assert(0.0 == t1.x1());
    assert(0.0 == t1.y1());

    Rectangle t2(Point(5.5, 6.9));
    assert(0.0 == t2.x0());
    assert(0.0 == t2.y0());
    assert(5.5 == t2.x1());
    assert(6.9 == t2.y1());

    Rectangle t3(Point(10.1, 1), Point(0, -1));
    assert(10.1 == t3.x0());
    assert(1 == t3.y0());
    assert(0.0 == t3.x1());
    assert(-1 == t3.y1());

    //c
    assert("[0.000000:0.000000, 0.000000:0.000000]" == to_string(t1));
    assert("[0.000000:5.500000, 0.000000:6.900000]" == to_string(t2));
    assert("[10.100000:0.000000, 1.000000:-1.000000]" == to_string(t3));

    //d
    assert(0 == t1.width());
    assert(5.5 == t2.width());
    assert(-10.1 == t3.width());
    assert(-2 == t3.height());

    //e
    assert(!t1.is_valid());
    assert(t2.is_valid());
    assert(!t3.is_valid());

    Rectangle t4 = t2.transpose();
    assert(t4.is_valid());

    Rectangle t5 = t3.transpose();
    assert(!t5.is_valid());

    Rectangle t6 = rectangle_union(t4, t5);
    assert(!t6.is_valid());

    //f
    assert(t4.x0() == t2.y0());
    assert(t4.y0() == t2.x0());
    assert(t4.x1() == t2.y1());
    assert(t4.y1() == t2.x1());

    //g
    assert(!t3.contains(Point(-1,0)));
    assert(!t3.contains(Point(5,0)));
    assert(t4.contains(Point(6,3)));

    assert(!t3.contains(t1));
    assert(!t6.contains(t4));
    assert(!t6.contains(t5));

    //h
    assert(t2.contains(rectangle_intersection(t2, t4)));
    assert(t4.contains(rectangle_intersection(t2, t4)));
    assert(!rectangle_intersection(t1, t2).is_valid());
    assert(t1 == rectangle_intersection(t1, t3));


    std::cout << "alle Rectangle-Tests erfolgreich\n";
}

int main()
{
    testRectangle();
}