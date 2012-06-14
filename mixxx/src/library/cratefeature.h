#ifndef CRATEFEATURE_H
#define CRATEFEATURE_H

#include <QSqlTableModel>
#include <QModelIndex>
#include <QAction>

#include "library/libraryfeature.h"
#include "library/cratetablemodel.h"

#include "treeitemmodel.h"
#include "configobject.h"

class TrackCollection;

class CrateFeature : public LibraryFeature {
    Q_OBJECT
  public:
    CrateFeature(QObject* parent, TrackCollection* pTrackCollection, ConfigObject<ConfigValue>* pConfig);
    virtual ~CrateFeature();

    QVariant title();
    QIcon getIcon();

    bool dropAccept(QUrl url);
    bool dropAcceptChild(const QModelIndex& index, QUrl url);
    bool dragMoveAccept(QUrl url);
    bool dragMoveAcceptChild(const QModelIndex& index, QUrl url);

    void bindWidget(WLibrarySidebar* sidebarWidget,
                    WLibrary* libraryWidget,
                    MixxxKeyboard* keyboard);

    TreeItemModel* getChildModel();

  public slots:
    void activate();
    void activateChild(const QModelIndex& index);
    void onRightClick(const QPoint& globalPos);
    void onRightClickChild(const QPoint& globalPos, QModelIndex index);
    void onLazyChildExpandation(const QModelIndex& index);

    void slotCreateCrate();
    void slotDeleteCrate();
    void slotRenameCrate();
    void slotToggleCrateLock();
    void slotImportPlaylist();
    void slotExportPlaylist();
    void slotCrateTableChanged(int playlistId);

  private:
    QString getRootViewHtml() const;
    QModelIndex constructChildModel(int selected_id);
    void clearChildModel();

    TrackCollection* m_pTrackCollection;
    CrateDAO& m_crateDao;
    QAction *m_pCreateCrateAction;
    QAction *m_pDeleteCrateAction;
    QAction *m_pRenameCrateAction;
    QAction *m_pLockCrateAction;
    QAction *m_pImportPlaylistAction;
    QAction *m_pExportPlaylistAction;
    QSqlTableModel m_crateListTableModel;
    CrateTableModel m_crateTableModel;
    QModelIndex m_lastRightClickedIndex;
    TreeItemModel m_childModel;
    ConfigObject<ConfigValue>* m_pConfig;
};

#endif /* CRATEFEATURE_H */