if grub-file --is-x86-multiboot myos.bin; then
  echo multiboot confirmed
  return 0
else
  echo the file is not multiboot
  return 1
fi
