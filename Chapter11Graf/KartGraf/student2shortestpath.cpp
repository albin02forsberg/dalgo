#include "student2shortestpath.h"

#include <queue>
#include <assert.h>
#include <QDebug>

using namespace std;



const char* nameOfStudent2(){
    return "Homer Simpson";
}


vector<Ixnode> shortestPathBetweenNodes(const std::vector<Node>& graph,
                                        Ixnode ixStart, Ixnode ixStop, IVisualFeedback* pFeedback){

    // Jag låter diverse deklarationer ligga kvar, men du kan ta bort dem om du vill!
    // Deklarationerna skapar den tabell (infoAboutNode)
    // och den kö (inputsToBeExaminedsom) jag använde på föreläsningen.

    struct Nodeinfo{
        Ixnode m_ixPrevious;
        bool   m_hasKnownDistance;
        Nodeinfo(Ixnode ixPrevious=-1, bool hasKnownDistance = false)
            : m_ixPrevious(ixPrevious),m_hasKnownDistance(hasKnownDistance) {}
    };

    struct Input{
        Ixnode m_ixFrom;
        Ixnode m_ixTo;
        float  m_accumulatedCost;

        Input(Ixnode ixFrom=-1,Ixnode ixTo=-1,  float accumulatedCost=2e20) : m_ixFrom(ixFrom), m_ixTo(ixTo),  m_accumulatedCost(accumulatedCost) {}

        bool operator()(const Input& a, const Input& b ) const {
                return a.m_accumulatedCost > b.m_accumulatedCost;
        }
    };

    qDebug() << "isStart = " << ixStart << ", ixStop " << ixStop;

    vector<Nodeinfo>  infoAboutNode(graph.size(), Nodeinfo());

    priority_queue<Input, vector<Input>, Input> inputsToBeExamined;


    inputsToBeExamined.push( Input(-1, ixStart, 0.0) );


    while (!inputsToBeExamined.empty()){

        // TODO
    }



}





vector<Ixnode> shortestPathBetweenNodes2(const std::vector<Node>& graph,
                                        Ixnode ixStart, Ixnode ixStop, IVisualFeedback* pFeedback){


    // Denna funktion är inget uppdrag.
    // (Den kommer att anropas om A* är aktiverad)

}
