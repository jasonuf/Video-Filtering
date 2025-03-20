#include "pool.h"

Pool::Pool(QWidget *parent)
    : QWidget{parent}
{
    masterLayout = new QVBoxLayout();
    tempLayout = new QHBoxLayout();
    masterLayout->addLayout(tempLayout);
    setLayout(masterLayout);
}

void Pool::addClips(QStringList *list)
{
    for (int i = 0; i < list->size(); ++i)
    {
        qInfo() << "String in List : " << list->at(i);

        tempFileName = list->at(i);
        tempUrl = QUrl::fromLocalFile(list->at(i));
        clips.push_back(new VideoClip(this));
        clips[clips.size()-1]->setSource(tempUrl);

        int slashPos;
        for (int j = list->at(i).size() - 1; j >= 0 ; --j)
        {
            if (list->at(i)[j] == "/")
            {
                slashPos = j;
                break;
            }
        }

        tempFileName.slice(slashPos + 1);

        clips[clips.size()-1]->setFileName(tempFileName);

        qInfo() <<"Temp URL: " << tempUrl << " Clip: " << clips[clips.size()-1] << " File Name set to: " << clips[clips.size()-1]->getFileName();

        clipDisplays.push_back(new ClipDisplay(nullptr, clips[clips.size()-1]));
    }

    addToPool(list->size());

    //str to url conversion
    //testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));
}

void Pool::addToPool(uint num)
{


    // QPalette bluePal = QPalette();
    // bluePal.setColor(QPalette::Window, Qt::blue);

    // testWidget = new QWidget();
    // testWidget->setAutoFillBackground(true);
    // testWidget->setPalette(bluePal);
    // testWidget->setFixedSize(200,200);
    // tempLayout->addWidget(testWidget);

    // for (VideoClip* c : clipList)
    // {
    //     tempLayout->addLayout(new ClipDisplay(nullptr, c), 1);
    // }

    for (int i = clipDisplays.size() - num; i < clipDisplays.size(); ++i)
    {
        tempLayout->addLayout(clipDisplays[i]);
    }

    qInfo() << "Clips: " << clips;
    qInfo() << "clipDisplays: " << clipDisplays;

}
