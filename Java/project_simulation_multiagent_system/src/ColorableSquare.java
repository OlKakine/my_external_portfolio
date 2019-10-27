import gui.*;
import java.awt.Color;
import java.awt.Graphics2D;

public class ColorableSquare implements GraphicalElement{
	private Rectangle rectangle;
	private int size;
	private int x,y;
	private Color fillColor;
	private Color drawColor;

	public ColorableSquare(int x, int y, Color drawColor, Color fillColor, int size){
		this.rectangle = new Rectangle(x,y,drawColor, fillColor, size);
		this.size = size;
		this.x = x;
		this.y = y;
		this.fillColor = fillColor;
		this.drawColor = drawColor;
	}

	@Override
	public void paint(java.awt.Graphics2D g2d){
		rectangle.paint(g2d);
	}

	public void changeColor(Color fillColor){
		if(fillColor == this.fillColor) return;
		this.rectangle = new Rectangle(this.x, this.y, this.drawColor, fillColor, this.size);
		this.fillColor = fillColor;
	}

	public Color getColor(){
		return this.fillColor;
	}
}
