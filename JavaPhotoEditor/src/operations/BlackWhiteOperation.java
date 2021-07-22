package operations;

import java.util.ArrayList;

import gui.Layer;
import gui.Selection;

public class BlackWhiteOperation extends Operation {

	@Override
	public void execute(Layer i, int num) {
		Selection s = i.parent.getSelection();
		ArrayList<Integer> indexes = s.pixelSelection(i.width, i.height);
		
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				if((i.pixels.get(j).A + i.pixels.get(j).B + i.pixels.get(j).G + i.pixels.get(j).R) < 3) {
				i.pixels.get(j).B = 0;
				i.pixels.get(j).G = 0;
				i.pixels.get(j).R = 0;
				}
				else {					
					i.pixels.get(j).B = (byte) 255;
					i.pixels.get(j).G = (byte) 255;
					i.pixels.get(j).R = (byte) 255;
				}
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				if((i.pixels.get(index).A + i.pixels.get(index).B + i.pixels.get(index).G + i.pixels.get(index).R) < 3) {
					i.pixels.get(index).B = 0;
					i.pixels.get(index).G = 0;
					i.pixels.get(index).R = 0;
					}
					else {					
						i.pixels.get(index).B = (byte) 255;
						i.pixels.get(index).G = (byte) 255;
						i.pixels.get(index).R = (byte) 255;
					}
			}
		}
	}
}
