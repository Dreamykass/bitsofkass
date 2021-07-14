#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treenode.h"
#include <QAbstractItemModel>
#include <QObject>
#include <QQmlListProperty>
#include <QVariant>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    Q_PROPERTY(QQmlListProperty<TreeNode> nodes READ nodes)
    Q_PROPERTY(QVariantList roles READ roles WRITE setRoles NOTIFY rolesChanged)
    Q_CLASSINFO("DefaultProperty", "nodes")

    TreeModel(QObject *parent = Q_NULLPTR);
    ~TreeModel();

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row,
                      int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QQmlListProperty<TreeNode> nodes();

    QVariantList roles() const;
    void setRoles(const QVariantList &roles);

    Q_INVOKABLE TreeNode *getNodeByIndex(const QModelIndex &index);
    Q_INVOKABLE QModelIndex getIndexByNode(TreeNode *node);
    Q_INVOKABLE bool insertNode(TreeNode *childNode,
                                const QModelIndex &parent = QModelIndex(),
                                int pos = (-1));

protected:
    TreeNode *getNode(const QModelIndex &index) const;

private:
    TreeNode *m_rootNode;
    QHash<int, QByteArray> m_roles;

signals:
    void rolesChanged();
};

#endif // TREEMODEL_H
