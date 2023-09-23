# Saga-TextEditor

## Overview:
Editor_Saga is a texteditor which is capable of opening very large(in GB's) text files
which cannot be opened by editors like vim, gedit, nano, kate like text editors.


## Internal Structure:
Internal Structure consist of, Array of structures having pointers pointing to particular line.
Line structure is implemented using linked list of gap buffer.
Gap buffer supports insertion and deletion with O(1) time complexity.

<img width="733" alt="image" src="https://user-images.githubusercontent.com/54500492/167610156-5a349cfd-98b8-4bb5-ab5a-3656a7640792.png">

## Support for large files:
At any instance only a page of file is stored in RAM. 2 files namely top and bottom are used as buffers which are stored on secondary storage,
hence editor can handle very large files.

<img width="717" alt="image" src="https://user-images.githubusercontent.com/54500492/167609832-bd9b3786-b74c-4e99-a087-0c88d897a49b.png">

