#!/usr/bin/env python3
##
## EPITECH PROJECT, 2025
## G-MAT-100-LYN-1-1-101pong-7
## File description:
## bonus.py
##

import os, sys, time, shutil, pyfiglet, emoji
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from rich.console import Console
from matrix_op import encrypt, decrypt

console = Console()

def clear():
    os.system("cls" if os.name == "nt" else "clear")

def center_text(text):
    terminal_size = shutil.get_terminal_size()
    width = terminal_size.columns
    lines = text.splitlines()
    centered_lines = []
    for line in lines:
        centered_lines.append(line.center(width))

    return "\n".join(centered_lines)

def menu():
    clear()
    title = pyfiglet.figlet_format("CIPHER", font="slant")
    print(center_text(title))

    menu_text = """
╔══════════════════════════════╗
║                              ║
      ║        [0] :locked: Cryptage       ║
         ║        [1] :unlocked: Décryptage     ║
           ║        [2] :cross_mark: QUITTER        ║
║                              ║
╚══════════════════════════════╝
"""
    menu_centered = center_text(menu_text)
    print(emoji.emojize(menu_centered))

    choix = input(("\n➤  Choice : "))
    clear()
    if choix == "0":
        message = input("Please enter your message to encrypte: ")
        key = input("Please enter your key to encrypte: ")
        print(center_text("Encryption in progress, please wait…"))
        time.sleep(2)
        clear()
        print(center_text(emoji.emojize("Done :check_mark_button:")))
        encrypt(message, key)
    elif choix == "1":
        message = input("Please enter your message to decrypte: ")
        key = input("Please enter your key to encrypte: ")
        print(center_text("Encryption in progress, please wait…"))
        time.sleep(2)
        clear()
        print(center_text(emoji.emojize("Done :check_mark_button:")))
        time.sleep(2)
        try:
            decrypt(message, key)
        except:
            print("indecipherable message")
    elif choix == "3":
        print(center_text(emoji.emojize("Goodbye !")))
        time.sleep(1)
        exit()
    else:
        print(center_text(":x: Choix invalide"))
        time.sleep(1)
    # menu()
menu()