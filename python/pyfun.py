#! /usr/bin/env python

import os, sys
import pygame
from pygame.locals import *
from helpers import *

if not pygame.font: print 'WARNING: Fonts Disabled'
if not pygame.mixer: print 'WARNING: Sound Disabled'

class ThisIsMain:
	def __init__ (self, width=640, height=480):
		pygame.init()

		self.width = width
		self.height = height

		self.screen = pygame.display.set_mode((self.width, self.height))

	def LoadSprites(self):
		self.cat = Cat()
		self.cat_sprites = pygame.sprite.RenderPlain((self.cat))

	def MainLoop(self):
		self.LoadSprites();
		BLACK = (0,0,0)
		while 1:
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					sys.exit()
				elif event.type == KEYDOWN:
					if ((event.key == K_RIGHT)
					or (event.key == K_LEFT)
					or (event.key == K_UP)
					or (event.key == K_DOWN)):
						self.cat.move(event.key)

			self.cat_sprites.draw(self.screen)
			pygame.display.flip()
			self.screen.fill(BLACK)

class Cat(pygame.sprite.Sprite):
	def __init__(self):
		pygame.sprite.Sprite.__init__(self)
		self.image, self.rect = load_image('sprites/cat.png', -1)
		self.x_dist = 8;
		self.y_dist = 8;

	def move(self, key):
		xmove = 0;
		ymove = 0;
		if (key == K_RIGHT):
			xmove = self.x_dist
		elif (key == K_LEFT):
			xmove = -self.x_dist
		elif (key == K_UP):
			ymove = -self.y_dist
		elif (key == K_DOWN):
			ymove = self.y_dist
		self.rect.move_ip(xmove, ymove);


#   executes the main loop 
if __name__ == "__main__":
	MainWindow = ThisIsMain()
	MainWindow.MainLoop()