#ifndef		__BABEL_CLIENT_PLUGIN_VIEW_H__
# define	__BABEL_CLIENT_PLUGIN_VIEW_H__

#include	<QUrl>
#include	<QQuickView>
#include	<QQmlContext>

#include	"./Common/IPluginView.h"

namespace	Babel
{
  namespace		Client
  {
    class			PluginView : public ::Babel::Client::Common::IPluginView
    {
    public:
    PluginView(QQuickView *view) : _view(view) {}
      ~PluginView(void) {}

    public:
      int		getHeight(void) const
      {
	return this->_view->height();
      }

      int		getWidth(void) const
      {
	return this->_view->width();
      }

      void		setSource(const QUrl &url)
      {
	this->_view->setSource(url);
      }

      void		show(void)
      {
#include <QDebug>
          qDebug() << this->_view->status();
          QQuickItem *item = this->_view->rootObject();
          item->setFlag(QQuickItem::ItemHasContents);
          item->update();
          this->_view->show();
      }

      QQuickItem	*getItem(void)
      {
	return this->_view->rootObject();
      }

      void		setContextProperty(const QString &name, QObject *context)
      {
        this->_view->rootContext()->setContextProperty(name, context);
      }

    private:
      QQuickView	*_view;
    };
  }
}
#endif // __BABEL_CLIENT_PLUGIN_VIEW_H__
