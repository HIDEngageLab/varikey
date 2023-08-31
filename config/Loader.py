# -*- coding: utf-8 -*-
#
# Copyright 2021 (C) by Roman Koch - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Testbench: Regression stoppen
#
# Roman Koch, koch.roman@googlemail.com

loader = None


class Loader:
    """
    load configuration file
    """

    current_station = 0

    def __init__(self, _filename=None):
        self.__filename = 'commander.config.json' if _filename is None else _filename
        self.__config = None

        import os
        assert os.path.isfile(self.__filename), \
            'key loader error: file ' + self.__filename + ' not found'

        self.__load()

    @property
    def config(self):
        return self.__config

    def reload(self):
        self.__load()

    def __load(self):
        self.__config = None
        with open(self.__filename, 'r') as config_file:
            try:
                import json
                _data = json.load(config_file)
                from commander.utilities.dict_tweaks import dict_to_type
                self.__config = dict_to_type('config', _data)
            except Exception as message:
                raise Exception('key loader: json load from ' + self.__filename + '\n%s' % message)
