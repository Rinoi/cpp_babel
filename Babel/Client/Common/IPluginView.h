#ifndef		__BABEL_CLIENT_COMMON_I_PLUGIN_VIEW_H__
# define	__BABEL_CLIENT_COMMON_I_PLUGIN_VIEW_H__

#include	<QUrl>
#include	<QQuickItem>

namespace	Babel
{
  namespace		Client
  {
    namespace			Common
    {
      class				IPluginView
      {
      public:
	virtual int		getHeight(void) const = 0;
	virtual int		getWidth(void) const = 0;
	virtual void		setSource(const QUrl &) = 0;
	virtual void		show(void) = 0;
	virtual QQuickItem	*getItem(void) = 0;
	virtual void		setContextProperty(const QString &, QObject *) = 0;
      };
    }
  }
}

#endif // __BABEL_CLIENT_COMMON_I_PLUGIN_VIEW_H__
