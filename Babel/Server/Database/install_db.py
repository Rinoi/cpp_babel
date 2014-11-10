#!  /usr/bin/env    python
#   coding:utf-8

from sqlalchemy import *

db = create_engine('mysql+mysqldb://babel:babel@localhost/babel')
db.echo = True
metadata = MetaData(db)

contact = Table('contact', metadata,
                Column('id', Integer, primary_key = True),
                Column('first_name', String(255), nullable = False),
                Column('last_name', String(255), nullable = False),
                Column('user_name', String(255), nullable = False),
                Column('email', String(255), nullable = False, unique = True),
                Column('password', String(255), nullable = False)
)
contact.create(checkfirst=True)


plugins = Table('plugins', metadata,
                Column('id', Integer, primary_key=True),
                Column('name', String(255), unique = True),
)
plugins.create(checkfirst=True)


try:
    req = plugins.insert()
    req.execute({'name' : 'connection'})
    req.execute({'name' : 'contactList'})
except:
    pass
