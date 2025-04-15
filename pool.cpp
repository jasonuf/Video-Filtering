#include "pool.h"

Pool::Pool(QWidget *parent)
    : QWidget{parent}
{
    lastRowIndex = -1;
    lastRowCols = 0;
    availableCols = 0;


    masterLayout = new QVBoxLayout();
    // tempLayout = new QHBoxLayout();
    // masterLayout->addLayout(tempLayout);
    setLayout(masterLayout);
}

std::vector<VideoClip *> &Pool::getClips()
{
    return clips;
}

void Pool::addClips(QStringList *list)
{
    for (int i = 0; i < list->size(); ++i) //handles each QString path that is uploaded
    {
        qInfo() << "String in List : " << list->at(i);

        tempFileName = list->at(i); //Grabs the full QString path to the video file
        tempUrl = QUrl::fromLocalFile(list->at(i)); //Grabs the path and converts it into the Url
        clips.push_back(new VideoClip(this)); //constructs the VideoClip into the clips vector
        clips[clips.size()-1]->setSource(tempUrl); //sets the source of the clip to the grabbed URL

        //algorithm finds the index of the last slash position in the string
        int slashPos;
        for (int j = list->at(i).size() - 1; j >= 0 ; --j)
        {
            if (list->at(i)[j] == "/")
            {
                slashPos = j;
                break;
            }
        }

        tempFileName.slice(slashPos + 1); //splices the string into just the last file name

        clips[clips.size()-1]->setFileName(tempFileName); //sets the clip's file name

        qInfo() <<"Temp URL: " << tempUrl << " Clip: " << clips[clips.size()-1] << " File Name set to: " << clips[clips.size()-1]->getFileName();

        clipDisplays.push_back(new ClipDisplay(nullptr, clips[clips.size()-1])); //constructs the clipDisplay struct based on the grabbed clip.
        //Connects the respective clip to signal after the thumbnail is loaded. Once it is, call the correct function
        connect(clipDisplays[clips.size()-1], &ClipDisplay::clipClicked,this, &Pool::clipClickRecieved);
        connect(clips[clips.size()-1], &VideoClip::thumbNailLoaded, this, &Pool::displayThumbnail);
    }

    //Call the addToPool and pass the number of clip displays to be updated
    addToPool(list->size());

    //str to url conversion
    //testUrl = QUrl::fromLocalFile(openVideoFilesList->at(0));
}

void Pool::addToPool(uint num)
{
    availableCols = this->parentWidget()->width() / 140;

    qInfo() << "Width: "<< width() << " Available cols: " << availableCols;

    for (int i = clipDisplays.size() - num; i < clipDisplays.size(); ++i) //handle each clip
    {
        if (lastRowIndex == -1)
        {
            addRow();
            rowLayouts[0]->addWidget(clipDisplays[i]);
            lastRowCols += 1;
        }

        else if (lastRowCols < availableCols)
        {
            rowLayouts[lastRowIndex]->addWidget(clipDisplays[i]);
            lastRowCols += 1;

            //rowLayouts[lastRowIndex]->addSpacing(125 * (availableCols - lastRowCols));
        }

        else
        {
            addRow();
            rowLayouts[lastRowIndex]->addWidget(clipDisplays[i]);
            lastRowCols = 1;


        }


        //tempLayout->addLayout(clipDisplays[i]);
    }

}

void Pool::displayThumbnail()
{
    //grab the sender object pointer then find the index of that object in clips list
    QObject* obj = sender();

    auto it = std::find(clips.begin(), clips.end(), obj);
    uint index = std::distance(clips.begin(), it);

    //grab the thumbnail since it is garunteed to be uploaded and then correctly add it to the label
    clipDisplays[index]->imagePix = QPixmap::fromImage(*clips[index]->getThumbnail());
    clipDisplays[index]->imagePix = clipDisplays[index]->imagePix.scaled(QSize(125,70), Qt::IgnoreAspectRatio);
    clipDisplays[index]->imageLabel->setPixmap(clipDisplays[index]->imagePix);

    // qInfo() << "index" << index << " Object: " << obj;
    // qInfo() << "image pix: " << &clipDisplays[index]->imagePix;
    // qInfo() << "iamge Label: " << clipDisplays[index]->imageLabel;

}

void Pool::clipClickRecieved(VideoClip *clip)
{
    emit sendClickedClip(clip);
}

void Pool::addRow()
{
    lastRowIndex += 1;
    QHBoxLayout* rowLayout = new QHBoxLayout();
    rowLayout->setAlignment(Qt::AlignLeft);
    rowLayout->maximumSize() = QSize(1000, 150);
    rowLayout->setSizeConstraint(QLayout::SetMaximumSize);
    // rowLayout->setSpacing(0);
    // rowLayout->setContentsMargins(0,0,0,0);
    rowLayouts.push_back(rowLayout);
    masterLayout->addLayout(rowLayout);
}

void Pool::removeRow()
{
    lastRowIndex -= 1;
    QHBoxLayout* lastRow = rowLayouts.back();
    masterLayout->removeItem(lastRow);
    rowLayouts.pop_back();
    delete lastRow;
}

void Pool::resizeEvent(QResizeEvent *event)
{
    // qInfo() << "New size " << width() << " Old size: " << event->oldSize();
    // QWidget::resizeEvent(event);
}


