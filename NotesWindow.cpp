#include "NotesWindow.hpp"

NotesWindow::NotesWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::NotesWindow){
    ui->setupUi(this);

    currentNoteId = -1;
    modified = false;

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,2);

    orderByName = new SmallButton(this);
    orderByName->setText(tr("Nombre"));
    orderByName->setCheckable(true);
    orderByName->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    orderByName->setToolTip(tr("Ordenar por nombre."));
    ui->horizontalLayout->addWidget(orderByName);

    orderByDate = new SmallButton(this);
    orderByDate->setText(tr("Fecha"));
    orderByDate->setCheckable(true);
    orderByDate->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    orderByDate->setToolTip(tr("Ordenar por fecha de creación."));
    ui->horizontalLayout->addWidget(orderByDate);

    desc = new SmallButton(this);
    desc->setText(tr("Desc."));
    desc->setCheckable(true);
    desc->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    desc->setColors(QColor(238,228,176));
    desc->setToolTip(tr("Ordenar de manera descendente."));
    ui->horizontalLayout->addWidget(desc);

    orderByDate->setChecked(true);

    notesList = ui->notesList;
    notesList->installEventFilter(this);

    contextMenu = new QMenu(this);
    QAction *deleteAction = new QAction(QIcon(":/icons/trash.png"),tr("Eliminar"),contextMenu);
    contextMenu->addAction(deleteAction);
    QObject::connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteSelectedNote()));

    QObject::connect(orderByName,SIGNAL(clicked()),this,SLOT(orderByNameClicked()));
    QObject::connect(orderByDate,SIGNAL(clicked()),this,SLOT(orderByDateClicked()));
    QObject::connect(desc,SIGNAL(clicked()),this,SLOT(orderDesc()));

    QObject::connect(notesList,SIGNAL(itemSelectionChanged()),this,SLOT(selectionChanged()));
    QObject::connect(notesList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
                     this,SLOT(currentItemChanged(QListWidgetItem*,QListWidgetItem*)));
    QObject::connect(ui->noteEdit,SIGNAL(textChanged()),this,SLOT(textModified()));

    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    QObject::connect(ui->actionNewNote,SIGNAL(triggered()),this,SLOT(newNote()));

}

NotesWindow::~NotesWindow()
{
    delete ui;
}

void NotesWindow::show()
{
    QMainWindow::show();
    notesDb.connect();
    constructList();
    cleanAndBlockEdition(true);
}

void NotesWindow::closeEvent(QCloseEvent *)
{
    notesDb.close();
}

bool NotesWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type()==QEvent::ContextMenu){
        QContextMenuEvent *contextEvent = static_cast<QContextMenuEvent*>(event);
        QListWidgetItem *item = notesList->itemAt(contextEvent->pos());
        if (item){
            contextMenu->exec(notesList->mapToGlobal(contextEvent->pos()));
        }
    }
    return QObject::eventFilter(object,event);
}

void NotesWindow::orderByNameClicked()
{
    orderByDate->setChecked(!orderByName->isChecked());
    constructList();
}

void NotesWindow::orderByDateClicked(){
    orderByName->setChecked(!orderByDate->isChecked());
    constructList();
}

void NotesWindow::orderDesc()
{
    constructList();
}

void NotesWindow::selectionChanged()
{
    cleanAndBlockEdition(false);
    int index = notesList->currentRow();
    if (index>=0){
        int nextNoteId = notesList->item(index)->data(Qt::UserRole).toInt();
        if (nextNoteId!=currentNoteId){
            currentNoteId = nextNoteId;
            ui->noteEdit->blockSignals(true);
            ui->noteEdit->setPlainText(notesDb.getNoteString(currentNoteId));
            ui->noteEdit->blockSignals(false);
        }
    }

}

void NotesWindow::currentItemChanged(QListWidgetItem *current, QListWidgetItem *)
{
    if (currentNoteId!=current->data(Qt::UserRole).toInt()){
        askForSave();
    }
}

void NotesWindow::save()
{
    if (currentNoteId<0){
        return;
    }

    if (notesDb.updateNote(currentNoteId,ui->noteEdit->toPlainText()))
    {
        setModified(false);
    }

}

void NotesWindow::textModified()
{
    setModified(true);
}

void NotesWindow::deleteSelectedNote()
{
    currentNoteId = -1;
    notesDb.deleteNote(notesList->currentItem()->data(Qt::UserRole).toInt());
    constructList();
    cleanAndBlockEdition(true);
}

void NotesWindow::newNote()
{
    askForSave();
    bool ok = false;
    QString name = QInputDialog::getText(this,tr("Nombre"),tr("Nombre de la nota: "),QLineEdit::Normal,"",&ok);
    if (ok){
        bool insertOk = false;
        currentNoteId = notesDb.newNote(name,&insertOk);
        if (insertOk){
            constructList();

            //Se selecciona la nota.
            for (int i = 0; i<notesList->count(); i++){
                if (notesList->item(i)->data(Qt::UserRole).toInt()==currentNoteId){
                    notesList->setCurrentRow(i);
                    break;
                }
            }
            //Se limpia el textedit.
            ui->noteEdit->blockSignals(true);
            ui->noteEdit->clear();
            ui->noteEdit->blockSignals(false);

        }
        else{
            QMessageBox::warning(this,tr("Error"),tr("No se pudo crear la nota."));
        }
    }
}

void NotesWindow::setModified(bool modified)
{
    setWindowModified(modified);
    this->modified = modified;
}

void NotesWindow::cleanAndBlockEdition(bool state)
{
    ui->noteEdit->blockSignals(true);
    ui->noteEdit->setEnabled(!state);
    if (state){
        ui->noteEdit->clear();
    }
    ui->noteEdit->blockSignals(false);
}

void NotesWindow::cleanList()
{
    for (int i=notesList->count(); i>0; i--){
        delete notesList->takeItem(i-1);
    }
}

void NotesWindow::makeList()
{
    int orderSelected = NotesDbInterface::ORDER_BY_DATE;
    if (orderByName->isChecked()){
        orderSelected = NotesDbInterface::ORDER_BY_NAME;
    }

    std::vector<NoteData> notesData = notesDb.getNotesInfo(orderSelected,desc->isChecked());
    for (unsigned int i = 0; i<notesData.size(); i++){
        QListWidgetItem  *item = new QListWidgetItem(notesData[i].getName());
        item->setToolTip(notesData[i].getDate().toString(QLocale::system().dateFormat()));
        item->setData(Qt::UserRole,QVariant(notesData[i].getId()));
        notesList->addItem(item);
    }
}

void NotesWindow::constructList()
{
    notesList->blockSignals(true);
    cleanList();
    makeList();
    notesList->blockSignals(false);
}

void NotesWindow::askForSave()
{
    if (modified && notesList->currentRow()>=0){
        int result = QMessageBox::information(this,
                                 tr("Confirmación"),
                                 tr("La nota actual no está guardada, ¿quieres guardarla?"),
                                 QDialogButtonBox::Yes,
                                 QDialogButtonBox::No);
        if (result==QDialogButtonBox::No){
            modified = false;
        }
        else if (result==QDialogButtonBox::Yes){
            save();
        }
    }
}
