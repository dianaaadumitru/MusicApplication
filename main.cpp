#include <iostream>
#include <QTWidgets/QApplication>
#include <string>
#include "../service/service.h"
#include <QMessageBox>
#include "../gui/gui2.h"
#include <QPushButton>

using namespace std;

int main(int argc, char *argv[]){
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication a(argc, argv);
    IFileRepo *r = nullptr;
    IFileRepo *watch = nullptr;
    r = new FileRepo("C:\\Users\\diana\\Desktop\\uni work\\2nd sem\\OOP\\a89-913-Dumitru-Diana\\tutorials.txt");

    QMessageBox msgBox{};
    msgBox.setWindowTitle("Watchlist type choice");
    msgBox.setText("Type of watchlist:");
    QPushButton *csv = msgBox.addButton("CSV", QMessageBox::ActionRole);
    QPushButton *html = msgBox.addButton("HTML", QMessageBox::ActionRole);

    msgBox.exec();
    if (msgBox.clickedButton() == csv){
        watch = new CSVRepo("C:\\Users\\diana\\Desktop\\uni work\\2nd sem\\OOP\\a67-913-Dumitru-Diana\\watchlist.csv");
    } else {
        watch = new HTMLRepo("C:\\Users\\diana\\Desktop\\uni work\\2nd sem\\OOP\\a67-913-Dumitru-Diana\\watchlist.html");
    }

    auto *service = new Service(r, watch);
    gui2 gui{service};
    gui.show();
    return a.exec();
}


/*
 Never Gonna Give You Up,Rick Astley,3,32,90000,https://www.youtube.com/watch?v=dQw4w9WgXcQ&list=RDdQw4w9WgXcQ&start_radio=1&t=18
I gotta feeling,The Black Eyed Peas,4,49,65895,https://www.youtube.com/watch?v=Wnn6M1nNiKQ
Pump it,The Black Eyed Peas,3,46,78903,https://www.youtube.com/watch?v=ZaI2IlHwmgQ
Memories,David Guetta,3,28,68000,https://www.youtube.com/watch?v=NUVCQXMUVnI
Can't hold us,Macklemore,7,3,12345,https://www.youtube.com/watch?v=2zNSgSzhBfM
The Nights,Avicii,3,10,83748,https://www.youtube.com/watch?v=UtF6Jej8yb4
Toxic,Britney Spears,3,31,23361,https://www.youtube.com/watch?v=LOZuxwVk7TU
A lalala long,Bob Marley,3,45,93729,https://www.youtube.com/watch?v=-JhwxTen6yA
I Need A Dollar,Aloe Blacc,4,3,23746,https://www.youtube.com/watch?v=Y6CJ_LG4YI4
Wake Me Up Before You Go-Go,Wham,3,53,63721,https://www.youtube.com/watch?v=pIgZ7gMze7A&list=RDdQw4w9WgXcQ&index=2
 */
