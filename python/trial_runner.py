import argparse
import os
import datetime
import subprocess
import sys

from coloring.luby_jones import Coloring
from models.graph import Graph
from models.vertex import Vertex
import util.file_reader

def main():
    """Run graph coloring."""
    
    # Command line interface
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--infile', action='store', metavar='',
        help='try algorithm on graph in this directory')
    parser.add_argument('-d', '--directory', action='store', metavar='',
        help='try algorithm on all graphs in this directory')
    parser.add_argument('-o', '--outdir', action='store', metavar='',
        help='write results to .csv file in this folder')
    parser.add_argument('-c', '--comment', action='store', metavar='',
        help='comment about this version of the code')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
        help='show additional console output')
    params = parser.parse_args()
    
    # Force prints to flush to console
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
    
    # Get graph name(s)
    if params.infile is not None:
        if not os.path.isdir(params.infile):
            raise ValueError('Infile directory does not exist.')
        file_paths = [params.infile]
            
    elif params.directory is not None:
        if not os.path.isdir(params.directory):
            raise ValueError('Directory does not exist.')
        file_paths = [params.directory + '\\' + x for x in os.listdir(params.directory)]
            
    else:
        raise ValueError('No directory or file name specified.')
        
    # Check outdir validity
    if params.outdir is not None and not os.path.isdir(params.outdir):
        raise ValueError('outdir directory does not exist.')
    
    # Data
    trial_data = {}
    trial_start = str(datetime.datetime.now())
    
    # Process each graph
    for file_path in file_paths:
        graph_data = {}
        
        # Get metadata
        graph_data['name'] = os.path.basename(file_path)
        graph_data['commit'] = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD']).strip()
        graph_data['comment'] = params.comment if params.comment is not None else ''
        if params.verbose:
            print 'PROCESSING GRAPH {name} USING COMMIT {commit} ({comment})'.format(**graph_data)
        
        # Read graph from file
        if params.verbose:
            print '- Reading file...',
        graph = util.file_reader.read_out_file(file_path)
        if params.verbose:
            print 'done'
        
        # Record starting time
        start = datetime.datetime.now()
        if params.verbose:
            print '- Start timestamp:', start
        
        # Color graph
        if params.verbose:
            print '- Coloring graph...',
        coloring = Coloring(graph)
        graph_data['colors'] = coloring.color(True, graph_data['comment'])
        if params.verbose:
            print 'done'
        
        # Record finishing time
        finish = datetime.datetime.now()
        graph_data['runtime'] = (finish - start).total_seconds()
        
        if params.verbose:
            print '- Finish timestamp:', finish
            print '- Runtime:', graph_data['runtime']
            print '- Colors:', graph_data['colors']
        
        # Add to results
        trial_data[graph_data['name']] = graph_data
        
        if params.verbose:
            print ' '
    
    # Print results to outdir
    if params.outdir is not None:
        if params.verbose:
            print 'Writing to outfile...',
    
        outfile_name = datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S') + '.csv'
        outfile = open(params.outdir + '\\' + outfile_name, 'w')
        for i in trial_data:
            outfile.write(trial_start + ',{commit},{comment},{name},{runtime},{colors}\n'.format(**trial_data[i]))
        outfile.close()
            
        if params.verbose:
            print 'done'
    
if __name__ == '__main__':
    main()