#include <ZyklotronController.h>
#include <boost/thread.hpp>
#include <fstream>

namespace BLL {

ZyklotronController::ZyklotronController() {
  // prepare html-Data
  to_log << "<!DOCTYPE html5>\n";
  to_log << "<html>\n";
  to_log << " <body>\n";
  to_log << "  <h1>Ergebnisse der Zyklotronsimulation</h1>\n";
  to_log << "  <table>\n";
}

void ZyklotronController::shut_down() {
  for (int i = 0; i < zyks.size(); i++) {
    zyks[i]->shutdown();
    if (zyks[i] != 0)
      delete zyks[i];
  }

  // postpeare html-Data
  to_log << "  </table\n";
  to_log << " </body>\n";
  to_log << "</html>";

  // write Data
  std::ofstream file{"log.html", ios::out};
  file << to_log.str();
  file.flush();
  file.close();
}

ZyklotronController::~ZyklotronController() {}

void ZyklotronController::addZyklotron(std::vector<std::string> strs) {
  names.push_back(strs);
  auto zyk = new Zyklotron();
  zyk->setGraphNames(strs);
  zyks.push_back(zyk);
}

Zyklotron &ZyklotronController::getZyklotron(int index) { return *zyks[index]; }

void ZyklotronController::run() {
  if (zyks.size() == 0) {
    return;
  }
  for (int i = 0; i < zyks.size(); i++) {
    zyks[i]->run();
  }
}
/* if true set GraphsNames of Zyk 1,2 3:
        123 123 123

   else
        111 222 333

*/
void ZyklotronController::insertGraphs(bool order) {
  if (order) {
    bool finish = false;
    int index = 0;
    while (!finish) {
      finish = true;
      for (int zyk = 0; zyk < zyks.size(); zyk++) {
        if (index < names[zyk].size()) {
          Window::instance().addGraph<StdGraphController>(names[zyk][index]);
          finish = false;
        }
      }
      index++;
    }
  }
}

void ZyklotronController::writeToLog(std::vector<std::string> names,
                                     ZyklotronParts::ZykSet data) {

  static boost::mutex writeToLogMtx;

  boost::unique_lock<boost::mutex> lock{writeToLogMtx};

  if (names.size() != 7)
    return;

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[0] << "</td><td>" << data.v.toString()
         << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[1] << "</td><td>" << data.roundtime.toString()
         << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[2] << "</td><td>"
         << data.timeInCondensator.toString() << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[3] << "</td><td>" << data.ke.toString()
         << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[4] << "</td><td>" << data.re.toString()
         << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[5] << "</td><td>" << data.me.toString()
         << "</td>\n";
  to_log << "   </tr>\n";

  to_log << "   <tr>\n";
  to_log << "    <td>" << names[6] << "</td><td>" << data.r.toString()
         << "</td>\n";
  to_log << "   </tr>\n";
}
}
