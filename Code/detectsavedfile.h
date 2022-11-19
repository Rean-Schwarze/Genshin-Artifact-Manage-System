#ifndef DETECTSAVEDFILE_H
#define DETECTSAVEDFILE_H

#include <QWidget>

namespace Ui {
class detectSavedFile;
}

class detectSavedFile : public QWidget
{
    Q_OBJECT

public:
    explicit detectSavedFile(QWidget *parent = nullptr);
    ~detectSavedFile();

private:
    Ui::detectSavedFile *ui;
};

#endif // DETECTSAVEDFILE_H
