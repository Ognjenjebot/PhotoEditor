package operations;

import java.util.ArrayList;

import gui.Layer;
import gui.Selection;

public class BasicOperation1 extends Operation {
	@Override
	public void execute(Layer i, int num) {
		Selection s = i.parent.getSelection();
		ArrayList<Integer> indexes = s.pixelSelection(i.width, i.height);
		
		
		if (indexes.size() == 0) {//cela slika
			for (int j=0; j<i.pixels.size(); j++) {
				i.pixels.get(j).A += num;
				i.pixels.get(j).R += num;
				i.pixels.get(j).G += num;
				i.pixels.get(j).B += num;
			}
		} else { //selekcija
			for (int j=0; j<indexes.size(); j++) {
				int index = indexes.get(j).intValue();
				i.pixels.get(index).A += num; //PAZI DA NE PRODJE [0,255]
				i.pixels.get(index).R += num;
				i.pixels.get(index).G += num;
				i.pixels.get(index).B += num;
			}
		}
	}
}
