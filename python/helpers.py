import os,sys
import pygame
from pygame.locals import *

if not pygame.font: print 'WARNING: Fonts Disabled'
if not pygame.mixer: print 'WARNING: Sound Disabled'

def load_image(name, colorkey=None):
	fullname = os.path.join('assets', name)
	try:
		image = pygame.image.load(fullname)
	except pygame.error, message:
		print 'Cannot load image: ' , name
		raise SystemExit, message
	image = image.convert()
	if colorkey is not None:
		if colorkey is -1:
			colorkey = image.get_at((0,0))
		image.set_colorkey(colorkey, RLEACCEL)
	return image, image.get_rect()

# def load_sound(name):