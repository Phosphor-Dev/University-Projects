public class mainClass{
    static void error(String msg){
        System.out.println(msg);
        System.exit(0);
    }
    static void println(String msg){
        System.out.println(msg);
    }

    public static void main(String[] args){
        if (args.length != 2){
            error("Expecting Two Args.");
        }

        Shape firstTriangle = new Triangle("FirstTriangle", Integer.valueOf(args[0]), Integer.valueOf(args[1]));
        Shape secondTriangle = new Triangle("SecondTriangle", Integer.valueOf(args[0]) - 1, Integer.valueOf(args[1]) - 1);
        Shape firstCircle = new Circle("FirstCircle", Integer.valueOf(args[0]));
        Shape secondCircle = new Circle("SecondCircle", Integer.valueOf(args[0]) - 1);
        Shape firstSquare = new Square("FirstSquare", Integer.valueOf(args[0]));
        Shape secondSquare = new Square("SecondSquare", Integer.valueOf(args[0]) - 1);
        Shape firstRectangle = new Rectangle("FirstRectangle", Integer.valueOf(args[0]), Integer.valueOf(args[1]));
        Shape secondRectangle = new Rectangle("SecondRectangle", Integer.valueOf(args[0]) - 1, Integer.valueOf(args[1]) - 1);

        Picture Picture1 = new Picture();

        Picture1.add(secondRectangle);
        Picture1.add(firstRectangle);
        Picture1.add(secondSquare);
        Picture1.add(firstSquare);
        Picture1.add(secondCircle);
        Picture1.add(firstCircle);
        Picture1.add(secondTriangle);
        Picture1.add(firstTriangle);

        Picture1.drawAll();
        Picture1.totalArea();
    }
}

class Shape{
    String name;
    Shape(String newName){
        name = newName;
    }
    double area(){
        return 0.0;
    }
    void draw(){
        System.out.println("Shape.draw() from Shape class called.");
    }

}

class Triangle extends Shape{
    double base;
    double height;

    Triangle(String newName, double base, double height) {
        super(newName);
        this.base = base;
        this.height = height;
    }
    double area(){
        return (this.base * this.height)/2;
    }
    void draw() {
        System.out.println(name + "(" + (int)this.base + ", " + (int)this.height + ") : " + String.format("%.2f", this.area()));

        System.out.println("*");
        System.out.println("* *");
        System.out.println("* * *");
        System.out.println("* * * *");
        System.out.println("* * * * *");
    }
}

class Circle extends Shape{
    double radius;
    Circle(String newName, double radius) {
        super(newName);
        this.radius = radius;
    }
    double area(){
        return 3.14159 * this.radius * this.radius;
    }
    void draw() {
        System.out.println(name + "(" + (int)this.radius + ") : " + String.format("%.2f", this.area()));

        System.out.println("  * * *  ");
        System.out.println("* * * * *");
        System.out.println("* * * * *");
        System.out.println("* * * * *");
        System.out.println("  * * *  ");
    }
}

class Square extends Shape{
    double base;
    Square(String newName, double base) {
        super(newName);
        this.base = base;
    }
    double area(){
        return this.base * this.base;
    }
    void draw() {
        System.out.println(name + "(" + (int)this.base + ", " + (int)this.base + ") : " + String.format("%.2f", this.area()));

        System.out.println("* * * * *");
        System.out.println("* * * * *");
        System.out.println("* * * * *");
        System.out.println("* * * * *");
        System.out.println("* * * * *");
    }
}

class Rectangle extends Square{
    double height;

    Rectangle(String newName, double base, double height) {
        super(newName, base);
        this.height = height;
    }

    double area(){
        return (this.base * this.height);
    }
    void draw() {
        System.out.println(name + "(" + (int)this.base + ", " + (int)this.height + ") : " + String.format("%.2f", this.area()));

        System.out.println("* * * * * * * * * *");
        System.out.println("* * * * * * * * * *");
        System.out.println("* * * * * * * * * *");
        System.out.println("* * * * * * * * * *");
        System.out.println("* * * * * * * * * *");
    }
}

class ListNode{
    Shape info;
    ListNode next;
    ListNode(Shape info, ListNode next){
        this.info = info;
        this.next = next;
    }
}

class Picture{
    ListNode head;
    Picture(){
        head = null;
    }
    void add (Shape sh){
        head = new ListNode(sh, head);
    }
    void drawAll(){
        for (ListNode p=head; p!=null; p=p.next){
            p.info.draw();
        }        
    }
    double totalArea(){
        double sum = 0.0;
        for (ListNode p=head; p!=null; p=p.next){
            sum += p.info.area();
        }
        System.out.println("Total : " + String.format("%.2f", sum));
        return sum;
    }
}
    
