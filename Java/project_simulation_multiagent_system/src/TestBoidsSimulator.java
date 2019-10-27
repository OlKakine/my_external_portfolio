import gui.GUISimulator;
import java.awt.Color;

public class TestBoidsSimulator {
	public static void main(String[] args){
		GUISimulator gui = new GUISimulator(500,500, Color.BLACK);
		BoidsSimulator boidsSimulator = new BoidsSimulator();
		gui.setSimulable(boidsSimulator);

		gui.addGraphicalElement(boidsSimulator.getBoidsGraphicalElement());		
	}
}
