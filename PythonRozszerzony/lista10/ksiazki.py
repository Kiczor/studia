from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime
from sqlalchemy import create_engine
import argparse

Base = declarative_base()
engine = create_engine('sqlite:///zadanie.db', echo=True)
Base.metadata.create_all(engine)

class Ksiazka( Base ):
	__tablename__ = 'Ksiazka'
	tytul = Column( String )
	autor = Column( String )
	rok = Column( Integer )
	#gdziejest = relationship( 'Znajomy' )
	gdziejest = Column( String, ForeignKey( 'Znajomy.id' ) )

class Znajomy( Base ):
	__tablename__ = 'Znajomy'
	id = Column( Integer )
	imie = Column( String )
	email = Column( String )
	#wypozyczone = Column( String, ForeignKey( 'Ksiazka.tytul' ) )
	wypozyczone = relationship('Ksiazka')
